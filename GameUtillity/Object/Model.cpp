#include "Model.h"
#include "CalcTransform.h"
#include "FileUtillity.h"
#include <cassert>
#include <fstream>
#include <sstream>

#pragma region ���O���

using std::unique_ptr;
using YGame::ModelObject;
using YGame::Model;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

#pragma endregion

#pragma region ���[�g�p�����[�^�ԍ�

static const UINT TraIndex	 = static_cast<UINT>(Model::Common::RootParameterIndex::TransformCB); // transform
static const UINT ColIndex	 = static_cast<UINT>(Model::Common::RootParameterIndex::ColorCB); // color
static const UINT LigIndex	 = static_cast<UINT>(Model::Common::RootParameterIndex::LightCB); // light
static const UINT MateIndex	 = static_cast<UINT>(Model::Common::RootParameterIndex::MaterialCB); // material
static const UINT TexIndex	 = static_cast<UINT>(Model::Common::RootParameterIndex::TexDT); // tex

#pragma endregion

#pragma region Static

std::vector<std::unique_ptr<Model>> Model::models_{};
Model::Common Model::common_{};
YDX::PipelineSet Model::Common::sPipelineSet_{};

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
	models_.push_back(std::move(newModel));

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
	models_.push_back(std::move(newModel));

	// ���f���|�C���^��Ԃ�
	return newModelPtr;
}

Model* Model::Load(const std::string& modelFileName, const bool isSmoothing)
{
	// �ǂݍ��񂾂��Ƃ����邩�`�F�b�N
	for (size_t i = 0; i < models_.size(); i++)
	{
		// �t�@�C���p�X �������Ȃ�
		if (modelFileName == models_[i]->fileName_)
		{
			// ���̃e�N�X�`���|�C���^��Ԃ�
			return models_[i].get();
		}
	}

	// ���f������
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// ���b�V������
	std::unique_ptr<Mesh> newMesh;

	// �t�@�C����
	std::string objFileName  = modelFileName + ".obj";
	objFileName = YUtil::FilePath(objFileName);
	std::string directoryPath = "Resources/Models/" + modelFileName + "/";

	// ���b�V�����[�h
	newMesh.reset(Mesh::Load(directoryPath, objFileName, isSmoothing));

	// �ǉ�
	newModel->meshes_.push_back(std::move(newMesh));

	// �t�@�C�������
	newModel->fileName_ = modelFileName;


	// �|�C���^���l��
	Model* newModelPtr = newModel.get();

	// ���f����ۑ�
	models_.push_back(std::move(newModel));

	// ���f���|�C���^��Ԃ�
	return newModelPtr;
}

void Model::AllClear()
{
	// ���f���S����
	for (size_t i = 0; i < models_.size(); i++)
	{
		models_[i].reset(nullptr);
	}
	models_.clear();
}

void Model::Draw(ModelObject* pObj)
{
	// �`�悵�Ȃ��Ȃ�e��
	if (isInvisible_) { return; }

	// �萔�o�b�t�@���V�F�[�_�[�ɑ���
	pObj->SetDrawCommand(TraIndex, ColIndex, LigIndex);

	// ���b�V�����ɈႤ�o�b�t�@
	for (size_t i = 0; i < meshes_.size(); i++)
	{
		// �`��
		meshes_[i]->Draw(MateIndex, TexIndex);
	}
}

#pragma endregion

#pragma region Common

void Model::Common::StaticInitialize()
{
	// �p�C�v���C��������
	std::unique_ptr<PipelineSet::IStatus> pplnState = std::make_unique<PipelineSetStatus>();
	sPipelineSet_.Initialize(pplnState.get());
}

void Model::Common::ShaderSet::Load(ID3DBlob* errorBlob)
{
	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/ModelVS.hlsl", "main", "vs_5_0", vs, errorBlob);
	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/ModelPS.hlsl", "main", "ps_5_0", ps, errorBlob);

	vsBlob_ = vs;
	psBlob_ = ps;
}

void Model::Common::PipelineSetStatus::Initialize(ID3DBlob* errorBlob_)
{
	// �V�F�[�_�[�ǂݍ���
	ShaderSet shdrs;
	shdrs.Load(errorBlob_);

	// ���_���C�A�E�g�̐ݒ�
	inputLayout_ =
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
		// �ڋ�_	 (x, y, z)
		{
			"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// ���_�F	 (x, y, z, w)
		{
			"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}
	};

	// �e�N�X�`���T���v���[�̐ݒ�
	{
		D3D12_STATIC_SAMPLER_DESC sampleDesc{};
		sampleDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // ���܂�Ԃ�   (�^�C�����O)
		sampleDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // �c�܂�Ԃ�   (�^�C�����O)
		sampleDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // ���s�܂�Ԃ� (�^�C�����O)
		sampleDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; // �{�[�_�[�̎��͍�
		sampleDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // �S�ă��j�A���
		sampleDesc.MaxLOD = D3D12_FLOAT32_MAX; // �~�j�}�b�v�ő�l
		sampleDesc.MinLOD = 0.0f;              // �~�j�}�b�v�ŏ��l
		sampleDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		sampleDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // �s�N�Z���V�F�[�_�[����̂ݎg�p�\

		sampleDesc_.push_back(sampleDesc);
	}

	// ���[�g�p�����[�^�̐ݒ�
	{
		size_t rpIdxCBNum = static_cast<size_t> (RootParameterIndex::TexDT);

		for (size_t i = 0; i < rpIdxCBNum; i++)
		{
			// �萔�o�b�t�@
			D3D12_ROOT_PARAMETER rootParam{};
			rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // �萔�o�b�t�@�r���[
			rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // �萔�o�b�t�@�ԍ�
			rootParam.Descriptor.RegisterSpace = 0;					  // �f�t�H���g�l
			rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

			rootParams_.push_back(rootParam);
		}

		// �f�X�N���v�^�����W�̐ݒ�
		descriptorRange_.NumDescriptors = 1; // 1�x�̕`��Ɏg���e�N�X�`����1���Ȃ̂�1
		descriptorRange_.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descriptorRange_.BaseShaderRegister = 0; // �e�N�X�`�����W�X�^0��
		descriptorRange_.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		// �e�N�X�`�����W�X�^
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange_;
		rootParam.DescriptorTable.NumDescriptorRanges = 1;
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

		rootParams_.push_back(rootParam);
	}

	// �p�C�v���C���ݒ�
	{
		// �V�F�[�_�[�̐ݒ�
		pipelineDesc_.VS.pShaderBytecode = shdrs.vsBlob_.Get()->GetBufferPointer();
		pipelineDesc_.VS.BytecodeLength = shdrs.vsBlob_.Get()->GetBufferSize();
		pipelineDesc_.PS.pShaderBytecode = shdrs.psBlob_.Get()->GetBufferPointer();
		pipelineDesc_.PS.BytecodeLength = shdrs.psBlob_.Get()->GetBufferSize();

		// ���X�^���C�U�̐ݒ�
		pipelineDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // �w�ʂ��J�����O

		// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
		pipelineDesc_.DepthStencilState.DepthEnable = true; // �[�x�e�X�g
		pipelineDesc_.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // �������݋���
		pipelineDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // ��������΍��i
		pipelineDesc_.DSVFormat = DXGI_FORMAT_D32_FLOAT; // �[�x�t�H�[�}�b�g

		// �}�`�̌`��ݒ�
		pipelineDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	}

	// �v���~�e�B�u�`��̐ݒ�
	primitive_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; // �O�p�`���X�g
}

void Model::Common::StaticSetPipeline()
{
	// �p�C�v���C�����Z�b�g
	sPipelineSet_.SetDrawCommand();
}

#pragma endregion
