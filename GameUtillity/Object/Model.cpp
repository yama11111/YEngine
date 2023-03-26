#include "Model.h"
#include "CalcTransform.h"
#include "FileUtillity.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma region ���O���

using YGame::ModelObject;
using YGame::ModelCommon;
using YGame::Model;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

#pragma endregion

#pragma region ���[�g�p�����[�^�ԍ�

static const UINT TraIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::TransformCB); // transform
static const UINT ColIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::ColorCB); // color
static const UINT LigIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::LightCB); // light
static const UINT MateIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::MaterialCB); // material
static const UINT TexIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::TexDT); // tex

#pragma endregion


#pragma region ModelObject

ModelObject* ModelObject::Create(const Status& status)
{
	// �C���X�^���X��Ԃ�
	return Create(status, nullptr, nullptr, nullptr);
}

ModelObject* ModelObject::Create(const Status& status, ViewProjection* pVP, Color* pColor, LightGroup* pLightGroup)
{
	// �C���X�^���X���� (���I)
	ModelObject* instance = new ModelObject();

	// �萔�o�b�t�@����
	instance->cBuff_.Create();

	// ������(�f�t�H���g)
	instance->Initialize(status);
	instance->SetViewProjection(pVP);
	instance->SetColor(pColor);
	instance->SetLightGroup(pLightGroup);

	// �C���X�^���X��Ԃ�
	return instance;
}

void ModelObject::SetViewProjection(ViewProjection* pVP)
{
	// null�Ȃ�
	if (pVP == nullptr)
	{
		// �f�t�H���g���
		pVP_ = sDefVP_.get();
		return;
	}

	// ���
	pVP_ = pVP;
}
void ModelObject::SetColor(Color* pColor)
{
	// null�Ȃ�
	if (pColor == nullptr)
	{
		// �f�t�H���g���
		pColor_ = sDefColor_.get();
		return;
	}

	// ���
	pColor_ = pColor;
}
void ModelObject::SetLightGroup(LightGroup* pLightGroup)
{
	// null�Ȃ�
	if (pLightGroup == nullptr)
	{
		// �f�t�H���g���
		pLightGroup_ = sDefLightGroup_.get();
		return;
	}

	// ���
	pLightGroup_ = pLightGroup;
}

void ModelObject::SetDrawCommand()
{
	// �s��
	cBuff_.map_->matWorld_ = m_;
	cBuff_.map_->matViewProj_ = pVP_->view_ * pVP_->pro_;
	cBuff_.map_->cameraPos_ = pVP_->eye_;
	cBuff_.SetDrawCommand(TraIndex);

	// �F
	pColor_->SetDrawCommand(ColIndex);

	// ��
	pLightGroup_->SetDrawCommand(LigIndex);
}

#pragma endregion


#pragma region Model

Model* Model::Create()
{
	// �C���X�^���X���� (���I)
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

	// �@�����v�Z
	CalculateNormals(v, i);

	// �N���A + ���T�C�Y(���b�V��1��)
	instance->meshes_.clear();
	instance->meshes_.resize(1);
	
	// ���_�C���f�b�N�X������(���)
	instance->meshes_[0].vtIdx_.Initialize(v, i);
	// �}�e���A��������
	instance->meshes_[0].mtrl_ = Material();

	// �C���X�^���X��Ԃ�
	return instance;
}

Model* Model::LoadObj(const std::string& modelFileName, const bool isSmoothing)
{
	// �C���X�^���X���� (���I)
	Model* instance = new Model();
	
	// �N���A + ���T�C�Y(���b�V��1��)
	instance->meshes_.clear();
	instance->meshes_.resize(1);

	// ���_
	std::vector<VData> v;
	// �C���f�b�N�X
	std::vector<uint16_t> i;
	// ���_�@���X���[�V���O�p�f�[�^
	std::unordered_map<unsigned short, std::vector<unsigned short>> sd;
	// �}�e���A��
	Material m;

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
	std::vector<Vector3> positions;
	// �@��
	std::vector<Vector3> normals;
	// UV���W
	std::vector<Vector2> uvs;

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
			m = Material::Load(directoryPath, mtlFileName);
		}

#pragma endregion

#pragma region ���_�f�[�^

		// �擪������ "v" �Ȃ璸�_���W
		if (key == "v")
		{	
			// ���_���W
			Vector3 pos;
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
			Vector2 uv;
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
			Vector3 normal;
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
				vData.pos_ = positions[static_cast<size_t>(idPositon - 1)];
				vData.normal_ = normals[static_cast<size_t>(idNormal - 1)];
				vData.uv_ = uvs[static_cast<size_t>(idTexcoord - 1)];

				// �ǉ�
				v.push_back(vData);
				// �ǉ�
				i.push_back(static_cast<uint16_t>(i.size()));
				// �ǉ�
				if (isSmoothing)
				{
					sd[idPositon].emplace_back(static_cast<unsigned short>(v.size() - 1));
				}
			}
		}

#pragma endregion

	}

	// �t�@�C�������
	file.close();

	// �X���[�V���O���邩
	if (isSmoothing)
	{
		// �X���[�V���O�v�Z
		CalculateSmoothedVertexNormals(v, sd);
	}


	// ���_�C���f�b�N�X������(���)
	instance->meshes_[0].vtIdx_.Initialize(v, i);
	// �X���[�X�f�[�^���
	instance->meshes_[0].smoothData_ = sd;
	// �}�e���A�����
	instance->meshes_[0].mtrl_ = m;

	// �C���X�^���X��Ԃ�
	return instance;
}

Model* Model::Load(const LoadStatus& status)
{
	// �C���X�^���X���� (���I)
	Model* instance = new Model();

	// �f�B���N�g���p�X�ݒ�
	std::string directoryPath = "Resources/Models/" + status.directoryPath_;

	// Assimp�ݒ�
	Assimp::Importer importer;
	int flag = 0;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_PreTransformVertices;
	flag |= aiProcess_CalcTangentSpace;
	flag |= aiProcess_GenSmoothNormals;
	flag |= aiProcess_GenUVCoords;
	flag |= aiProcess_RemoveRedundantMaterials;
	flag |= aiProcess_OptimizeMeshes;

	// �t�@�C�����J��
	const aiScene* scene = importer.ReadFile(directoryPath + status.modelFileName_, flag);
	if (scene == nullptr)
	{
		// �����Ȃ�G���[
		printf(importer.GetErrorString());
		printf("\n");
		assert(false);
	}

	/// �N���A + ���T�C�Y(���b�V���̐�����)
	instance->meshes_.clear();
	instance->meshes_.resize(scene->mNumMeshes);
	
	// ���b�V������
	for (size_t i = 0; i < instance->meshes_.size(); i++)
	{
		// ���_���ǂݍ���
		const aiMesh* pMesh = scene->mMeshes[i];
		instance->meshes_[i].vtIdx_ = 
			LoadVertices(pMesh, status.isInverseU_, status.isInverseV_, status.isNormalized_);

		// �}�e���A���ǂݍ���
		const aiMaterial* pMaterial = scene->mMaterials[i];
		instance->meshes_[i].mtrl_ = 
			Material::Load(directoryPath, pMaterial, status.extension_);
	}

	// �㏈��
	scene = nullptr;

	// �C���X�^���X��Ԃ�
	return instance;
}

void Model::Draw(ModelObject* pObj)
{
	// �`�悵�Ȃ��Ȃ�e��
	if (isInvisible_) { return; }

	// �萔�o�b�t�@���V�F�[�_�[�ɑ���
	pObj->SetDrawCommand();

	// ���b�V�����ɈႤ�o�b�t�@
	for (size_t i = 0; i < meshes_.size(); i++)
	{
		// �}�e���A��
		meshes_[i].mtrl_.SetDrawCommand(MateIndex, TexIndex);

		// ���_�o�b�t�@�𑗂� + �`��R�}���h
		meshes_[i].vtIdx_.Draw();
	}
}

#pragma endregion
