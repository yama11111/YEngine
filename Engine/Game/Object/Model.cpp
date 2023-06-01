#include "Model.h"
#include "CalcTransform.h"
#include "MathUtillity.h"
#include "FileUtillity.h"
#include <cassert>
#include <fstream>
#include <sstream>

#pragma region ���O���

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Model;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;
using YGame::DrawLocation;
using YGame::DrawLocationNum;

#pragma endregion

#pragma region ���[�g�p�����[�^�ԍ�

static const UINT TraIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::eTransformCB); // transform
static const UINT ColIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::eColorCB); // color
static const UINT MateIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::eMaterialCB); // material
static const UINT LigIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::eLightCB); // light
static const UINT TexConfigIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::eTexConfigCB); // texConfig
static const UINT TexIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::eTexDT); // tex

#pragma endregion

#pragma region Static

vector<unique_ptr<Model>> Model::sModels_{};
array<PipelineSet, Model::Pipeline::sShaderNum_> Model::Pipeline::sPipelineSets_{};
array<array<list<unique_ptr<Model::Pipeline::DrawSet>>, Model::Pipeline::sShaderNum_>, DrawLocationNum> Model::Pipeline::sDrawSets_;
FbxManager* Model::FbxLoader::sFbxMan_ = nullptr;
FbxImporter* Model::FbxLoader::sFbxImp_ = nullptr;

#pragma endregion


#pragma region Model

Model* Model::CreateCube()
{
	// ���f������
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// ���b�V������
	std::unique_ptr<Mesh> newMesh;

	// ���b�V�����[�h
	newMesh.reset(Mesh::CreateCube());

	// �ǉ�
	newModel->meshes_.push_back(std::move(newMesh));


	// �|�C���^���l��
	Model* newModelPtr = newModel.get();

	// ���f����ۑ�
	sModels_.push_back(std::move(newModel));

	// ���f���|�C���^��Ԃ�
	return newModelPtr;
}

Model* Model::CreateCube(const std::string& texFileName)
{
	// ���f������
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// ���b�V������
	std::unique_ptr<Mesh> newMesh;

	// ���b�V�����[�h
	newMesh.reset(Mesh::CreateCube(texFileName));

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
	objFileName = YUtil::FilePath(objFileName);
	

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

void Model::SetDrawCommand(Object* pObj, const DrawLocation& location, const ShaderType& shaderType)
{
	// �`��Z�b�g�}��
	Pipeline::StaticPushBackDrawSet(this, pObj, location, shaderType);
}

void Model::SetIsVisible(const bool isVisible)
{
	isVisible_ = isVisible;
}

#pragma endregion


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


#pragma region Object

Model::Object* Model::Object::Create(
	const Status& status,
	ViewProjection* pVP,
	CBColor* pColor,
	CBMaterial* pMaterial,
	CBLightGroup* pLightGroup,
	CBTexConfig* pTexConfig,
	const bool isMutable)
{
	// �C���X�^���X���� (���I)
	Object* instance = new Object();

	// �萔�o�b�t�@����
	instance->cBuff_.Create(isMutable);

	// ������(�f�t�H���g)
	instance->Initialize(status);
	instance->SetViewProjection(pVP);
	instance->SetMaterial(pMaterial);
	instance->SetColor(pColor);
	instance->SetLightGroup(pLightGroup);
	instance->SetTexConfig(pTexConfig);

	// �C���X�^���X��Ԃ�
	return instance;
}

void Model::Object::SetDrawCommand(
	const UINT transformRPIndex,
	const UINT colorRPIndex,
	const UINT materialRPIndex, 
	const UINT lightRPIndex,
	const UINT texConfigRPIndex)
{
	// �s��
	cBuff_.map_->matWorld_ = m_;
	cBuff_.map_->matViewProj_ = pVP_->view_ * pVP_->pro_;
	cBuff_.map_->cameraPos_ = pVP_->eye_;
	cBuff_.SetDrawCommand(transformRPIndex);

	// �F
	pColor_->SetDrawCommand(colorRPIndex);

	// �}�e���A��
	pMaterial_->SetDrawCommand(materialRPIndex);

	// ��
	pLightGroup_->SetDrawCommand(lightRPIndex);

	// �e�N�X�`���ݒ�
	pTexConfig_->SetDrawCommand(texConfigRPIndex);
}

void Model::Object::SetViewProjection(ViewProjection* pVP)
{
	// null�Ȃ�
	if (pVP == nullptr)
	{
		// �f�t�H���g���
		pVP_ = Default::sVP_.get();
		return;
	}

	// ���
	pVP_ = pVP;
}

void Model::Object::SetColor(CBColor* pColor)
{
	// null�Ȃ�
	if (pColor == nullptr)
	{
		// �f�t�H���g���
		pColor_ = Default::sColor_.get();
		return;
	}

	// ���
	pColor_ = pColor;
}

void Model::Object::SetMaterial(CBMaterial* pMaterial)
{
	// null�Ȃ�
	if (pMaterial == nullptr)
	{
		// �f�t�H���g���
		pMaterial_ = Default::sMaterial_.get();
		return;
	}

	// ���
	pMaterial_ = pMaterial;
}

void Model::Object::SetLightGroup(CBLightGroup* pLightGroup)
{
	// null�Ȃ�
	if (pLightGroup == nullptr)
	{
		// �f�t�H���g���
		pLightGroup_ = Default::sLightGroup_.get();
		return;
	}

	// ���
	pLightGroup_ = pLightGroup;
}

void Model::Object::SetTexConfig(CBTexConfig* pTexConfig)
{
	// null�Ȃ�
	if (pTexConfig == nullptr)
	{
		// �f�t�H���g���
		pTexConfig_ = Default::sTexConfig_.get();
		return;
	}

	// ���
	pTexConfig_ = pTexConfig;
}

unique_ptr<YGame::ViewProjection> Model::Object::Default::sVP_ = nullptr;
unique_ptr<YGame::CBColor> Model::Object::Default::sColor_ = nullptr;
unique_ptr<YGame::CBMaterial> Model::Object::Default::sMaterial_ = nullptr;
unique_ptr<YGame::CBLightGroup> Model::Object::Default::sLightGroup_ = nullptr;
unique_ptr<YGame::CBTexConfig> Model::Object::Default::sTexConfig_ = nullptr;

void Model::Object::Default::StaticInitialize()
{
	// ���� + ������ (�r���[�v���W�F�N�V�����|�C���^)
	sVP_.reset(new YGame::ViewProjection());
	sVP_->Initialize();

	// ���� + ������ (�F)
	sColor_.reset(CBColor::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));

	// ���� + ������ (�}�e���A��)
	sMaterial_.reset(CBMaterial::Create({ 1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f }, 1.0f, false));

	// ���� + ������ (�����|�C���^)
	sLightGroup_.reset(CBLightGroup::Create({ 1.0f,1.0f,1.0f }, false));

	// ���� + ������ (�e�N�X�`���ݒ�)
	sTexConfig_.reset(CBTexConfig::Create({ 1.0f,1.0f }, {}, false));
}

#pragma endregion


#pragma region �V�F�[�_�[�ԍ�

static const UINT DefaultIndex	 = static_cast<UINT>(Model::ShaderType::eDefault);
static const UINT PhongIndex	 = static_cast<UINT>(Model::ShaderType::ePhong);
static const UINT ToonIndex		 = static_cast<UINT>(Model::ShaderType::eToon);

#pragma endregion


#pragma region Pipeline

void Model::Pipeline::ShaderSet::Load()
{

	// �G���[�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	// phong
	{
		ID3DBlob* vs = nullptr;
		ID3DBlob* ps = nullptr;

		// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/PhongVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
		// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/PhongPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		phongVSBlob_ = vs;
		phongPSBlob_ = ps;
	}

	// toon
	{
		ID3DBlob* vs = nullptr;
		ID3DBlob* ps = nullptr;

		// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/ToonVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
		// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/ToonPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		toonVSBlob_ = vs;
		toonPSBlob_ = ps;
	}

	// Default
	{
		ID3DBlob* vs = nullptr;
		ID3DBlob* ps = nullptr;

		// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/ModelVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
		// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/ModelPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		defaultVSBlob_ = vs;
		defaultPSBlob_ = ps;
	}

}

void Model::Pipeline::StaticInitialize()
{

#pragma region �V�F�[�_�[�ǂݍ���

	// �V�F�[�_�[
	ShaderSet shdrs;
	
	// �ǂݍ���
	shdrs.Load();

#pragma endregion


#pragma region ���_���C�A�E�g�̐ݒ�


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

#pragma endregion


#pragma region �e�N�X�`���T���v���[�̐ݒ�

	// �e�N�X�`���T���v���[�z��
	std::vector<D3D12_STATIC_SAMPLER_DESC> samplerDescs;

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
	samplerDescs.push_back(samplerDesc);

#pragma endregion


#pragma region ���[�g�p�����[�^�̐ݒ�

	// ���[�g�p�����[�^
	std::vector<D3D12_ROOT_PARAMETER> rootParams;

	// �萔�o�b�t�@�̐�
	size_t rpIdxCBNum = static_cast<size_t> (RootParameterIndex::eTexDT);

	// �萔�o�b�t�@�̐�����
	for (size_t i = 0; i < rpIdxCBNum; i++)
	{
		// �萔�o�b�t�@
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // �萔�o�b�t�@�r���[
		rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // �萔�o�b�t�@�ԍ�
		rootParam.Descriptor.RegisterSpace = 0;					  // �f�t�H���g�l
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

		// �z��ɑ}��
		rootParams.push_back(rootParam);
	}

	// �f�X�N���v�^�����W�̐ݒ�
	D3D12_DESCRIPTOR_RANGE descriptorRange{};
	descriptorRange.NumDescriptors = 1; // 1�x�̕`��Ɏg���e�N�X�`����1���Ȃ̂�1
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0; // �e�N�X�`�����W�X�^0��
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// �e�N�X�`�����W�X�^
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

	// �z��ɑ}��
	rootParams.push_back(rootParam);

#pragma endregion


#pragma region �p�C�v���C���ݒ�

	// �p�C�v���C���ݒ�
	std::array<D3D12_GRAPHICS_PIPELINE_STATE_DESC, sPipelineSets_.size()> pipelineDescs{};

	// �V�F�[�_�[�̐ݒ�
	pipelineDescs[PhongIndex].VS.pShaderBytecode	 = shdrs.phongVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[PhongIndex].VS.BytecodeLength		 = shdrs.phongVSBlob_.Get()->GetBufferSize();
	pipelineDescs[PhongIndex].PS.pShaderBytecode	 = shdrs.phongPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[PhongIndex].PS.BytecodeLength		 = shdrs.phongPSBlob_.Get()->GetBufferSize();

	pipelineDescs[ToonIndex].VS.pShaderBytecode		 = shdrs.toonVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[ToonIndex].VS.BytecodeLength		 = shdrs.toonVSBlob_.Get()->GetBufferSize();
	pipelineDescs[ToonIndex].PS.pShaderBytecode		 = shdrs.toonPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[ToonIndex].PS.BytecodeLength		 = shdrs.toonPSBlob_.Get()->GetBufferSize();

	pipelineDescs[DefaultIndex].VS.pShaderBytecode	 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[DefaultIndex].VS.BytecodeLength	 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[DefaultIndex].PS.pShaderBytecode	 = shdrs.defaultPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[DefaultIndex].PS.BytecodeLength	 = shdrs.defaultPSBlob_.Get()->GetBufferSize();

	// �p�C�v���C���̐�����
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// �T���v���}�X�N�̐ݒ�
		pipelineDescs[i].SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

		// ���X�^���C�U�̐ݒ�
		pipelineDescs[i].RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
		pipelineDescs[i].RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����
		pipelineDescs[i].RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // �w�ʂ��J�����O

		// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
		pipelineDescs[i].DepthStencilState.DepthEnable = true; // �[�x�e�X�g
		pipelineDescs[i].DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // �������݋���
		pipelineDescs[i].DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // ��������΍��i
		pipelineDescs[i].DSVFormat = DXGI_FORMAT_D32_FLOAT; // �[�x�t�H�[�}�b�g

		// �u�����h�X�e�[�g
		D3D12_RENDER_TARGET_BLEND_DESC& blendDesc = pipelineDescs[i].BlendState.RenderTarget[0];
		blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA�S�Ẵ`�����l����`��

		blendDesc.BlendEnable = true;                // �u�����h��L���ɂ���
		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD; // ���Z
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;   // �\�[�X�̒l��100%�g��
		blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO; // �f�X�g�̒l��  0%�g��

		// ����������
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;			 // ���Z
		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;      // �\�[�X�̃A���t�@�l
		blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - �\�[�X�̃A���t�@�l

		// �}�`�̌`��ݒ�
		pipelineDescs[i].PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		// ���_���C�A�E�g�̐ݒ�
		pipelineDescs[i].InputLayout.pInputElementDescs = inputLayout.data(); // ���_���C�A�E�g�̐擪�A�h���X
		pipelineDescs[i].InputLayout.NumElements = (UINT)inputLayout.size(); // ���_���C�A�E�g��

		// ���̑��̐ݒ�
		pipelineDescs[i].NumRenderTargets = 1; // �`��Ώۂ�1��
		pipelineDescs[i].RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255�w���RGBA
		pipelineDescs[i].SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O
	}

#pragma endregion


#pragma region �v���~�e�B�u�`��̐ݒ�

	// �v���~�e�B�u�`��
	D3D_PRIMITIVE_TOPOLOGY primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; // �O�p�`���X�g

#pragma endregion


	// �p�C�v���C���̐�����
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// �p�C�v���C��������
		sPipelineSets_[i].Initialize(samplerDescs, rootParams, pipelineDescs[i], primitive);
	}

	// �`��ꏊ�̐�����
	for (size_t i = 0; i < sDrawSets_.size(); i++)
	{
		// �ϊ�
		DrawLocation location = static_cast<DrawLocation>(i);

		// �N���A
		StaticClearDrawSet(location);
	}
}

void Model::Pipeline::StaticClearDrawSet(const DrawLocation& location)
{
	// �C���f�b�N�X�ɕϊ�
	size_t index = static_cast<size_t>(location);

	// �p�C�v���C���̐�����
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// ����Ȃ�
		if (sDrawSets_[index][i].empty() == false)
		{
			// �N���A
			sDrawSets_[index][i].clear();
		}
	}
}

void Model::Pipeline::StaticPushBackDrawSet(
	Model* pModel, Model::Object* pObj, 
	const DrawLocation& location, const ShaderType& shaderType)
{
	// �`��Z�b�g����
	unique_ptr<Pipeline::DrawSet> newDrawSet = std::make_unique<Pipeline::DrawSet>();

	// ������
	newDrawSet->pModel_ = pModel;
	newDrawSet->pObj_ = pObj;
	
	// �C���f�b�N�X�ɕϊ�
	size_t locationIdx = static_cast<size_t>(location);

	// �C���f�b�N�X�ɕϊ�
	size_t shaderIdx = static_cast<size_t>(shaderType);

	// �}��
	sDrawSets_[locationIdx][shaderIdx].push_back(std::move(newDrawSet));
}

void Model::Pipeline::StaticDraw(const DrawLocation& location)
{
	// �C���f�b�N�X�ɕϊ�
	size_t index = static_cast<size_t>(location);

	// �p�C�v���C���̐�����
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// �p�C�v���C�����Z�b�g
		sPipelineSets_[i].SetDrawCommand();

		// ���f���`��
		for (std::unique_ptr<DrawSet>& drawSet : sDrawSets_[index][i])
		{
			// �`��
			drawSet->Draw();
		}
	}
}

void Model::Pipeline::DrawSet::Draw()
{
	// �`�悵�Ȃ��Ȃ�e��
	if (pModel_->isVisible_ == false) { return; }

	// �萔�o�b�t�@���V�F�[�_�[�ɑ���
	pObj_->SetDrawCommand(TraIndex, ColIndex, MateIndex, LigIndex, TexConfigIndex);

	// ���b�V�����ɈႤ�o�b�t�@
	for (size_t i = 0; i < pModel_->meshes_.size(); i++)
	{
		// �`��
		pModel_->meshes_[i]->Draw(TexIndex);
	}
}

#pragma endregion


