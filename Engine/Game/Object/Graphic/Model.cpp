#include "Model.h"
#include "MathVector.h"
#include "MathUtil.h"
#include "FileUtil.h"
#include <cassert>
#include <fstream>
#include <sstream>

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Model;
using YGame::PipelineSetting;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

vector<unique_ptr<Model>> Model::sModels_{};
FbxManager* Model::FbxLoader::sFbxMan_ = nullptr;
FbxImporter* Model::FbxLoader::sFbxImp_ = nullptr;

Model* Model::CreateCube(const std::unordered_map<std::string, Texture*>& pTexs)
{
	// ���f������
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// ���b�V������
	std::unique_ptr<Mesh> newMesh;

	// ���b�V�����[�h
	newMesh.reset(Mesh::CreateCube(pTexs));

	// �ǉ�
	newModel->meshes_.push_back(std::move(newMesh));


	// �|�C���^���l��
	Model* newModelPtr = newModel.get();

	// ���f����ۑ�
	sModels_.push_back(std::move(newModel));

	// ���f���|�C���^��Ԃ�
	return newModelPtr;
}

Model* Model::LoadObj(const std::string& modelFileName, const bool isSmoothing)
{
	// �ǂݍ��񂾂��Ƃ����邩�`�F�b�N
	for (size_t i = 0; i < sModels_.size(); i++)
	{
		// �t�@�C���p�X �������Ȃ�
		if (modelFileName == sModels_[i]->fileName_)
		{
			// ���̃e�N�X�`���|�C���^��Ԃ�
			return sModels_[i].get();
		}
	}

	// ���f������
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// ���b�V������
	std::unique_ptr<Mesh> newMesh;

	// �f�B���N�g���p�X (���f���̃t�@�C�����Ɠ����t�H���_����)
	std::string directoryPath = "Resources/Models/" + modelFileName + "/";

	// FBX�t�@�C����
	std::string objFileName = modelFileName + ".obj";
	objFileName = YFile::FilePath(objFileName);


	// ���b�V�����[�h
	newMesh.reset(Mesh::LoadObj(directoryPath, objFileName, isSmoothing));

	// �ǉ�
	newModel->meshes_.push_back(std::move(newMesh));

	// �t�@�C�������
	newModel->fileName_ = modelFileName;


	// �|�C���^���l��
	Model* newModelPtr = newModel.get();

	// ���f����ۑ�
	sModels_.push_back(std::move(newModel));

	// ���f���|�C���^��Ԃ�
	return newModelPtr;
}

Model* Model::LoadFbx(const std::string& modelFileName, const bool isSmoothing)
{
	// �ǂݍ��񂾂��Ƃ����邩�`�F�b�N
	for (size_t i = 0; i < sModels_.size(); i++)
	{
		// �t�@�C���p�X �������Ȃ�
		if (modelFileName == sModels_[i]->fileName_)
		{
			// ���̃e�N�X�`���|�C���^��Ԃ�
			return sModels_[i].get();
		}
	}

	// ���f������
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// ���b�V������
	std::unique_ptr<Mesh> newMesh;

	// �f�B���N�g���p�X (���f���̃t�@�C�����Ɠ����t�H���_����)
	std::string directoryPath = "Resources/Models/" + modelFileName + "/";

	// FBX�t�@�C����
	std::string fbxFileName = modelFileName + ".fbx";

	//�t���p�X
	std::string fullPath = directoryPath + fbxFileName;

	// �t�@�C�������
	newModel->fileName_ = modelFileName;

	// �t�@�C�������w�肵��FBX�t�@�C���ǂݍ���
	assert(FbxLoader::sFbxImp_->Initialize(fullPath.c_str(), -1, FbxLoader::sFbxMan_->GetIOSettings()));


	// �V�[������
	FbxScene* fbxScene = FbxScene::Create(FbxLoader::sFbxMan_, "fbxScene");

	// �t�@�C�����烍�[�h����FBX�����C���|�[�g
	FbxLoader::sFbxImp_->Import(fbxScene);


	// FBX�m�[�h�̐�
	int nodeCount = fbxScene->GetNodeCount();

	// �K�v���̃������m�� (�A�h���X�̂����\�h)
	newModel->nodes_.reserve(nodeCount);

	// ���[�g�m�[�h���珇�ɉ�͂��ă��f���ɗ�������
	FbxLoader::ParseNodeRecursive(newModel.get(), fbxScene->GetRootNode(), isSmoothing);


	// FBX�V�[���J��
	fbxScene->Destroy();


	// �|�C���^���l��
	Model* newModelPtr = newModel.get();

	// ���f����ۑ�
	sModels_.push_back(std::move(newModel));

	// ���f���|�C���^��Ԃ�
	return newModelPtr;
}

void Model::AllClear()
{
	// ���f���S����
	for (size_t i = 0; i < sModels_.size(); i++)
	{
		sModels_[i].reset(nullptr);
	}
	sModels_.clear();
}

void Model::SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices)
{
	if (isVisible_ == false) { return; }
	
	// ���b�V�����ɈႤ�o�b�t�@�ŕ`��
	for (size_t i = 0; i < meshes_.size(); i++)
	{
		meshes_[i]->SetDrawCommand(rpIndices);
	}
}

PipelineSetting Model::GetPipelineSetting()
{
	PipelineSetting result;

	// ���_���C�A�E�g
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout =
	{
		// ���_���W	 (x, y, z)
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// �@��		 (x, y, z)
		{
			"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// UV���W	 (x, y)
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		//// �ڋ�_	 (x, y, z)
		//{
		//	"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		//},
		//// ���_�F	 (x, y, z, w)
		//{
		//	"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		//}
	};

	result.inputLayout = inputLayout;
	
	// �e�N�X�`���T���v���[�̐ݒ�
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // ���܂�Ԃ�   (�^�C�����O)
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // �c�܂�Ԃ�   (�^�C�����O)
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // ���s�܂�Ԃ� (�^�C�����O)
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; // �{�[�_�[�̎��͍�
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // �S�ă��j�A���
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX; // �~�j�}�b�v�ő�l
	samplerDesc.MinLOD = 0.0f;              // �~�j�}�b�v�ŏ��l
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // �s�N�Z���V�F�[�_�[����̂ݎg�p�\

	// �e�N�X�`���T���v���[�z��ɑ}��
	result.samplerDescs.emplace_back(samplerDesc);
	
	result.fillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�

	result.cullMode = D3D12_CULL_MODE_BACK; // �w�ʂ��J�����O
	
	result.depthEnable = true; // �[�x�e�X�g���s��

	result.primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; // �O�p�`

	result.primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; // �O�p�`���X�g

	return result;
}


#pragma region FbxLoader

void Model::FbxLoader::StaticInitialize()
{
	// �ď������`�F�b�N
	assert(sFbxMan_ == nullptr);

	// FBX�}�l�[�W���[�̐���
	sFbxMan_ = FbxManager::Create();

	// FBX�}�l�[�W���[�̓��o�͐ݒ�
	FbxIOSettings* ios = FbxIOSettings::Create(sFbxMan_, IOSROOT);
	sFbxMan_->SetIOSettings(ios);

	// FBX�C���|�[�^�[�̐���
	sFbxImp_ = FbxImporter::Create(sFbxMan_, "");
}

void Model::FbxLoader::StaticFinalize()
{
	// �e��FBX�C���X�^���X�j��
	sFbxImp_->Destroy();
	sFbxMan_->Destroy();
}

void Model::FbxLoader::ParseNodeRecursive(Model* pModel, FbxNode* fbxNode, const bool isSmoothing, Node* parent)
{
	// �m�[�h����
	std::unique_ptr<Node> newNode = std::make_unique<Node>();


	// �m�[�h��
	newNode->name_ = fbxNode->GetName();


	// FBX�m�[�h�̃��[�J�����
	FbxDouble3 fbxPos = fbxNode->LclTranslation.Get();
	FbxDouble3 fbxRot = fbxNode->LclRotation.Get();
	FbxDouble3 fbxScale = fbxNode->LclScaling.Get();

	// �ϊ�
	Vector3 pos = { static_cast<float>(fbxPos[0]), static_cast<float>(fbxPos[1]), static_cast<float>(fbxPos[2]) };
	Vector3 rot = { static_cast<float>(fbxRot[0]), static_cast<float>(fbxRot[1]), static_cast<float>(fbxRot[2]) };
	Vector3 scale = { static_cast<float>(fbxScale[0]), static_cast<float>(fbxScale[1]), static_cast<float>(fbxScale[2]) };

	// ��]�p�� Degree -> Radian��
	rot.x_ = YMath::ConvertFromDegreeToRadian(rot.x_);
	rot.y_ = YMath::ConvertFromDegreeToRadian(rot.y_);
	rot.z_ = YMath::ConvertFromDegreeToRadian(rot.z_);

	// ���[�J���g�����X�t�H�[��������
	newNode->local_.Initialize({ pos, rot, scale });

	// �O���[�o���ό`�s��̌v�Z
	newNode->globalMat_ = newNode->local_.m_;

	// �e������Ȃ�
	if (parent)
	{
		// ���
		newNode->parent_ = parent;

		// �e�s�����Z
		newNode->globalMat_ *= parent->globalMat_;
	}

	// �|�C���^�擾
	Node* pNewNode = newNode.get();

	// �m�[�h�z��ɒǉ�
	pModel->nodes_.push_back(std::move(newNode));


	// FBX�m�[�h�̃��b�V���������
	FbxNodeAttribute* fbxNodeAttribute = fbxNode->GetNodeAttribute();

	// ���b�V����񂪂���Ȃ�
	if (fbxNodeAttribute)
	{
		// ���b�V���Ȃ�
		if (fbxNodeAttribute->GetAttributeType() == FbxNodeAttribute::EType::eMesh)
		{
			// ���b�V������
			std::unique_ptr<Mesh> newMesh;

			// ���b�V�����[�h
			newMesh.reset(Mesh::LoadFbx("Resources/Models/" + pModel->fileName_ + "/", fbxNode, isSmoothing));

			// �ǉ�
			pModel->meshes_.push_back(std::move(newMesh));
		}
	}


	// �q�m�[�h�ɑ΂��čċA�Ăяo��
	for (int i = 0; i < fbxNode->GetChildCount(); i++)
	{
		ParseNodeRecursive(pModel, fbxNode->GetChild(i), isSmoothing, pNewNode);
	}
}

#pragma endregion
