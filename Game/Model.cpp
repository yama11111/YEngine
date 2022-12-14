#include "Model.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma comment(lib, "assimp-vc143-mtd.lib")

using Game::Model;

DX::PipelineSet Model::pplnSet_;

void Model::StaticInitialize(std::vector<D3D12_ROOT_PARAMETER>* rootParams)
{
	pplnSet_.Initialize(DX::PipelineSet::Type::ModelT, rootParams);
}

void Model::StaticSetDrawCommand()
{
	pplnSet_.SetDrawCommand();
}

Model* Model::Create()
{
	// �C���X�^���X
	Model* instance = new Model();

	// ���_
	std::vector<DX::ModelVData> v =
	{
		// �O
		{{ -1.0f, -1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // ����
		{{ -1.0f,  1.0f, -1.0f }, {}, {0.0f, 0.0f}}, // ����
		{{  1.0f, -1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // �E��
		{{  1.0f,  1.0f, -1.0f }, {}, {1.0f, 0.0f}}, // �E��

		// ��
		{{ -1.0f, -1.0f,  1.0f }, {}, {1.0f, 1.0f}}, // ����
		{{ -1.0f,  1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // ����
		{{  1.0f, -1.0f,  1.0f }, {}, {0.0f, 1.0f}}, // �E��
		{{  1.0f,  1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // �E��

		// ��
		{{ -1.0f, -1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // ����
		{{ -1.0f, -1.0f,  1.0f }, {}, {0.0f, 1.0f}}, // ����
		{{ -1.0f,  1.0f, -1.0f }, {}, {1.0f, 0.0f}}, // �E��
		{{ -1.0f,  1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // �E��

		// �E
		{{  1.0f, -1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // ����
		{{  1.0f, -1.0f,  1.0f }, {}, {1.0f, 1.0f}}, // ����
		{{  1.0f,  1.0f, -1.0f }, {}, {0.0f, 0.0f}}, // �E��
		{{  1.0f,  1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // �E��

		// ��
		{{ -1.0f, -1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // ����
		{{ -1.0f, -1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // ����
		{{  1.0f, -1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // �E��
		{{  1.0f, -1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // �E��

		// ��
		{{ -1.0f,  1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // ����
		{{ -1.0f,  1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // ����
		{{  1.0f,  1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // �E��
		{{  1.0f,  1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // �E��
	};
	// �C���f�b�N�X
	std::vector<uint16_t> i =
	{
		// �O
		0, 1, 2, // �O�p�`1��
		2, 1, 3, // �O�p�`2��

		// ��
		6, 7, 4, // �O�p�`1��
		4, 7, 5, // �O�p�`2��

		// ��
		8, 9, 10, // �O�p�`1��
		10, 9, 11, // �O�p�`2��

		// �E
		14, 15, 12, // �O�p�`1��
		12, 15, 13, // �O�p�`2��

		// ��
		16, 17, 18, // �O�p�`1��
		18, 17, 19, // �O�p�`2��

		//// ��
		22, 23, 20, // �O�p�`1��
		20, 23, 21, // �O�p�`2��
	};

	instance->meshes_.clear();
	instance->meshes_.resize(1);
	instance->meshes_[0].vtIdx_.Initialize(v, i, true);
	instance->meshes_[0].mtrl_ = Material();

	return instance;
}

Model* Model::Load(const std::string& modelFileName)
{
	// �C���X�^���X
	Model* instance = new Model();
	instance->meshes_.clear();
	instance->meshes_.resize(1);

	// ���_
	std::vector<DX::ModelVData> v;
	// �C���f�b�N�X
	std::vector<uint16_t> i;

	// �t�@�C���X�g���[��
	std::ifstream file;

	// �t�@�C����
	std::string objFileName  = modelFileName + ".obj";
	std::string directoryPath = "Resources/Models/" + modelFileName + "/";
	// .obj�t�@�C�����J��
	file.open(directoryPath + objFileName);
	// �t�@�C���I�[�v�����s���`�F�b�N
	assert(file);

	// ���_���W
	std::vector<Math::Vec3> positions;
	// �@��
	std::vector<Math::Vec3> normals;
	// UV���W
	std::vector<Math::Vec2> uvs;

	// 1�s���ǂݍ���
	std::string line;
	while (std::getline(file, line))
	{
		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream lineStream(line);

		// ���p�X�y�[�X��؂�ōs�̐擪��������擾
		std::string key;
		std::getline(lineStream, key, ' ');

#pragma region �}�e���A��

		// �擪������ "mtllib" �Ȃ�}�e���A��
		if (key == "mtllib")
		{
			// �}�e���A���t�@�C�����擾
			std::string mtlFileName;
			lineStream >> mtlFileName;
			// �}�e���A���ǂݍ���
			instance->meshes_[0].mtrl_.Load(directoryPath, mtlFileName);
		}

#pragma endregion

#pragma region ���_�f�[�^

		// �擪������ "v" �Ȃ璸�_���W
		if (key == "v")
		{	
			// ���_���W
			Math::Vec3 pos;
			// �ǂݍ���
			lineStream >> pos.x_;
			lineStream >> pos.y_;
			lineStream >> pos.z_;	
			// �ǉ�
			positions.push_back(pos);
		}
		// �擪������ "vt" �Ȃ�e�N�X�`��
		if (key == "vt")
		{
			// UV���W
			Math::Vec2 uv;
			// �ǂݍ���
			lineStream >> uv.x_;
			lineStream >> uv.y_;
			// v���]
			//uv.y_ = 1.0f - uv.y_;
			// �ǉ�
			uvs.push_back(uv);
		}
		// �擪������ "vn" �Ȃ�@���x�N�g��
		if (key == "vn")
		{
			// �@��
			Math::Vec3 normal;
			// �ǂݍ���
			lineStream >> normal.x_;
			lineStream >> normal.y_;
			lineStream >> normal.z_;
			// �ǉ�
			normals.push_back(normal);
		}

#pragma endregion

#pragma region �C���f�b�N�X�f�[�^

		// �擪������ "f" �Ȃ�|���S��(�O�p�`)
		if (key == "f")
		{
			// ���p�X�y�[�X��؂�ōs�̑����ǂݍ���
			std::string indexString;
			while (std::getline(lineStream, indexString, ' '))
			{
				// ���_�C���f�b�N�X1���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
				std::istringstream indexStream(indexString);

				// �C���f�b�N�X�f�[�^
				uint16_t idPositon, idNormal, idTexcoord;
				
				// �ǂݍ���
				indexStream >> idPositon;
				// '/' ��΂�
				indexStream.seekg(1, std::ios_base::cur);
				// �ǂݍ���
				indexStream >> idTexcoord;
				// '/' ��΂�
				indexStream.seekg(1, std::ios_base::cur);
				// �ǂݍ���
				indexStream >> idNormal;

				// ���_�f�[�^
				DX::ModelVData vData;
				vData.pos_ = positions[idPositon - 1];
				vData.normal_ = normals[idNormal - 1];
				vData.uv_ = uvs[idTexcoord - 1];

				// �ǉ�
				v.push_back(vData);
				// �ǉ�
				i.push_back(static_cast<uint16_t>(i.size()));
			}
		}

#pragma endregion

	}

	file.close();

	instance->meshes_[0].vtIdx_.Initialize(v, i, false);

	return instance;
}

Model* Model::Load(const LoadStatus& state)
{
	// �C���X�^���X
	Model* instance = new Model();

	std::string directoryPath = "Resources/Models/" + state.directoryPath_;

	Assimp::Importer importer;
	int flag = 0;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_PreTransformVertices;
	flag |= aiProcess_CalcTangentSpace;
	flag |= aiProcess_GenSmoothNormals;
	flag |= aiProcess_GenUVCoords;
	flag |= aiProcess_RemoveRedundantMaterials;
	flag |= aiProcess_OptimizeMeshes;

	const aiScene* scene = importer.ReadFile(directoryPath + state.modelFileName_, flag);
	if (scene == nullptr)
	{
		printf(importer.GetErrorString());
		printf("\n");
		assert(false);
	}

	instance->meshes_.clear();
	instance->meshes_.resize(scene->mNumMeshes);
	for (size_t i = 0; i < instance->meshes_.size(); i++)
	{
		// ���_���ǂݍ���
		const aiMesh* pMesh = scene->mMeshes[i];
		instance->meshes_[i].vtIdx_ = 
			LoadVertices(pMesh, state.isInverseU_, state.isInverseV_, state.isNormalized_);

		// �}�e���A���ǂݍ���
		const aiMaterial* pMaterial = scene->mMaterials[i];
		instance->meshes_[i].mtrl_ = 
			LoadMaterial(directoryPath, pMaterial, state.extension_);
	}

	scene = nullptr;

	return instance;
}

DX::VertexIndex3D Game::Model::LoadVertices(const aiMesh* src, bool invU, bool invV, bool isNormalized)
{
	DX::VertexIndex3D vtIdx;

	aiVector3D zero3D(0.0f, 0.0f, 0.0f);
	aiColor4D zeroColor(0.0f, 0.0f, 0.0f, 0.0f);

	std::vector<DX::ModelVData> vData;
	std::vector<uint16_t> indices;

	vData.resize(src->mNumVertices);

	for (size_t i = 0; i < src->mNumVertices; ++i)
	{
		aiVector3D* position = &(src->mVertices[i]);
		aiVector3D* normal = &(src->mNormals[i]);
		aiVector3D* uv = (src->HasTextureCoords(0)) ? &(src->mTextureCoords[0][i]) : &zero3D;
		aiVector3D* tangent = (src->HasTangentsAndBitangents()) ? &(src->mTangents[i]) : &zero3D;
		aiColor4D* color = (src->HasVertexColors(0)) ? &(src->mColors[0][i]) : &zeroColor;

		if (invU) { uv->x = 1.0f - uv->x; }
		if (invV) { uv->y = 1.0f - uv->y; }

		DX::ModelVData vertex = {};
		vertex.pos_ = Math::Vec3(position->x, position->y, position->z);
		vertex.normal_ = Math::Vec3(normal->x, normal->y, normal->z);
		vertex.uv_ = Math::Vec2(uv->x, uv->y);
		vertex.tangent_ = Math::Vec3(tangent->x, tangent->y, tangent->z);
		vertex.color_ = Math::Vec4(color->r, color->g, color->b, color->a);

		vData[i] = vertex;
	}

	indices.resize(src->mNumFaces * 3);

	for (size_t i = 0; i < src->mNumFaces; ++i)
	{
		const aiFace& face = src->mFaces[i];

		indices[i * 3 + 0] = face.mIndices[0];
		indices[i * 3 + 1] = face.mIndices[1];
		indices[i * 3 + 2] = face.mIndices[2];
	}

	vtIdx.Initialize(vData, indices, isNormalized);

	return vtIdx;
}

Game::Material Game::Model::LoadMaterial(const std::string directoryPath, const aiMaterial* src, 
	const std::string extension)
{
	Material material;

	aiString path;
	if (src->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS)
	{
		std::string fileName = std::string(path.C_Str());
		if (extension != "")
		{
			fileName = ReplaceExtension(fileName, extension);
		}
		material.LoadTexture(directoryPath, fileName);
	}
	else
	{
		material = Material();
	}

	return material;
}

std::string Model::ReplaceExtension(const std::string fileName, const std::string extention)
{
	std::string result = fileName;

	std::string::size_type pos;
	pos = result.find_last_of(".");

	if (pos == std::string::npos) { return fileName; }

	return result.substr(0, pos) + "." + extention;
}

void Model::Draw(Object& obj, const ViewProjection& vp, const UINT tex)
{
	obj.SetDrawCommand(vp.view_, vp.pro_);

	for (size_t i = 0; i < meshes_.size(); i++)
	{
		meshes_[i].mtrl_.SetDrawCommand(tex);
		meshes_[i].vtIdx_.Draw();
	}
}

void Model::Draw(Object& obj, const ViewProjection& vp)
{
	obj.SetDrawCommand(vp.view_, vp.pro_);

	for (size_t i = 0; i < meshes_.size(); i++)
	{
		meshes_[i].mtrl_.SetDrawCommand();
		meshes_[i].vtIdx_.Draw();
	}
}
