#include "Model.h"
#include "CalcTransform.h"
#include "FilePath.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using YGame::ModelCommon;
using YGame::Model;
using YMath::Vec2;
using YMath::Vec3;
using YMath::Vec4;

const UINT ModIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::ModelCB);
const UINT ColIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::ColorCB);
const UINT MateIndex = static_cast<UINT>(ModelCommon::RootParameterIndex::MaterialCB);
const UINT TexIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::TexDT);

void Model::Draw(ObjectModel& obj, const ViewProjection& vp, Color& color, const UINT tex)
{
	obj.cBuff_.map_->mat_ = obj.m_ * vp.view_ * vp.pro_;
	obj.cBuff_.SetDrawCommand(ModIndex);

	color.SetDrawCommand(ColIndex);

	for (size_t i = 0; i < meshes_.size(); i++)
	{
		meshes_[i].mtrl_.cBuff_.SetDrawCommand(MateIndex);
		pTexManager_->SetDrawCommand(TexIndex, tex);
		meshes_[i].vtIdx_.Draw();
	}
}
void Model::Draw(ObjectModel& obj, const ViewProjection& vp, const UINT tex)
{
	Draw(obj, vp, defColor_, tex);
}
void Model::Draw(ObjectModel& obj, const ViewProjection& vp, Color& color)
{
	obj.cBuff_.map_->mat_ = obj.m_ * vp.view_ * vp.pro_;
	obj.cBuff_.SetDrawCommand(ModIndex);

	color.SetDrawCommand(ColIndex);

	for (size_t i = 0; i < meshes_.size(); i++)
	{
		meshes_[i].mtrl_.cBuff_.SetDrawCommand(MateIndex);
		pTexManager_->SetDrawCommand(TexIndex, meshes_[i].mtrl_.texIndex_);
		meshes_[i].vtIdx_.Draw();
	}
}
void Model::Draw(ObjectModel& obj, const ViewProjection& vp)
{
	Draw(obj, vp, defColor_);
}

Model* Model::Create()
{
	// �C���X�^���X
	Model* instance = new Model();

	// ���_
	std::vector<VData> v =
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

	Normalized(v, i);

	instance->meshes_.clear();
	instance->meshes_.resize(1);
	instance->meshes_[0].vtIdx_.Initialize(v, i);
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
	std::vector<VData> v;
	// �C���f�b�N�X
	std::vector<uint16_t> i;

	// �t�@�C���X�g���[��
	std::ifstream file;

	// �t�@�C����
	std::string objFileName  = modelFileName + ".obj";
	objFileName = YUtil::FilePath(objFileName);
	std::string directoryPath = "Resources/Models/" + modelFileName + "/";
	// .obj�t�@�C�����J��
	file.open(directoryPath + objFileName);
	// �t�@�C���I�[�v�����s���`�F�b�N
	assert(file);

	// ���_���W
	std::vector<Vec3> positions;
	// �@��
	std::vector<Vec3> normals;
	// UV���W
	std::vector<Vec2> uvs;

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
			instance->meshes_[0].mtrl_ = LoadMaterial(directoryPath, mtlFileName);
		}

#pragma endregion

#pragma region ���_�f�[�^

		// �擪������ "v" �Ȃ璸�_���W
		if (key == "v")
		{	
			// ���_���W
			Vec3 pos;
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
			Vec2 uv;
			// �ǂݍ���
			lineStream >> uv.x_;
			lineStream >> uv.y_;
			// v���]
			uv.y_ = 1.0f - uv.y_;
			// �ǉ�
			uvs.push_back(uv);
		}
		// �擪������ "vn" �Ȃ�@���x�N�g��
		if (key == "vn")
		{
			// �@��
			Vec3 normal;
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
				VData vData;
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

	instance->meshes_[0].vtIdx_.Initialize(v, i);

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
