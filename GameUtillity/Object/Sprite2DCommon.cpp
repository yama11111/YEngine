#include "Sprite2DCommon.h"
#include "CalcTransform.h"
#include <cassert>
#include <memory>

#pragma region ���O���

using YGame::Sprite2DObjectCommon;
using YGame::Sprite2DCommon;
using YDX::PipelineSet;

#pragma endregion


#pragma region Sprite2DObjectCommon

YMath::Matrix4 Sprite2DObjectCommon::sProjection_ = YMath::Matrix4::Identity();
std::unique_ptr<YGame::Color> Sprite2DObjectCommon::sDefColor_ = nullptr;

void Sprite2DObjectCommon::StaticInitialize()
{
	// �v���W�F�N�V�����s���ݒ�
	sProjection_ = YMath::MatOrthoGraphic();

	// ����
	sDefColor_.reset(Color::Create());
}

#pragma endregion


#pragma region Sprite2DCommon

PipelineSet Sprite2DCommon::sPipelineSet_;
YGame::TextureManager* Sprite2DCommon::spTexManager_ = nullptr;

void Sprite2DCommon::StaticInitialize()
{
	// ���
	spTexManager_ = TextureManager::GetInstance();

	// �p�C�v���C��������
	std::unique_ptr<PipelineSet::IStatus> pplnState = std::make_unique<PipelineSetStatus>();
	sPipelineSet_.Initialize(pplnState.get());
}

void Sprite2DCommon::ShaderSet::Load(ID3DBlob* errorBlob)
{
	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/Sprite2DVS.hlsl", "main", "vs_5_0", vs, errorBlob);
	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/Sprite2DPS.hlsl", "main", "ps_5_0", ps, errorBlob);

	vsBlob_ = vs;
	psBlob_ = ps;
}

void Sprite2DCommon::PipelineSetStatus::Initialize(ID3DBlob* errorBlob_)
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
		// UV���W	 (x, y)
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
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
		pipelineDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // �w�ʂ��J�����O���Ȃ�

		// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
		pipelineDesc_.DepthStencilState.DepthEnable = false; // �[�x�e�X�g���Ȃ�
		pipelineDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // ��ɏ㏑��

		// �}�`�̌`��ݒ�
		pipelineDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	}

	// �v���~�e�B�u�`��̐ݒ�
	primitive_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // �O�p�`�X�g���b�v
}

void Sprite2DCommon::StaticSetDrawCommand()
{
	// �p�C�v���C�����Z�b�g
	sPipelineSet_.SetDrawCommand();
}

#pragma endregion
