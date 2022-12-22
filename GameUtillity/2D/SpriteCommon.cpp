#include "SpriteCommon.h"
#include "CalcTransform.h"
#include <cassert>
#include <memory>

using YGame::SpriteCommon;
using YDX::PipelineSet;

YMath::Mat4 SpriteCommon::projection_ = YMath::Mat4::Identity();
PipelineSet SpriteCommon::pplnSet_;
YGame::TextureManager* SpriteCommon::pTexManager_ = nullptr;

void SpriteCommon::ShaderSet::Load(ID3DBlob* errorBlob)
{
	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/SpriteVS.hlsl", "main", "vs_5_0", vs, errorBlob);
	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/SpritePS.hlsl", "main", "ps_5_0", ps, errorBlob);

	vsBlob_ = vs;
	psBlob_ = ps;
}

void SpriteCommon::PipelineSetStatus::Initialize(ID3DBlob* errorBlob_)
{
	// �V�F�[�_�[�ǂݍ���
	ShaderSet shdrs;
	shdrs.Load(errorBlob_);

	// ���_���C�A�E�g�̐ݒ�
	inputLayout_ =
	{
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		{
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
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

	// �p�C�v���C���ݒ�
	{
		// �V�F�[�_�[�̐ݒ�
		pplnDesc_.VS.pShaderBytecode = shdrs.vsBlob_.Get()->GetBufferPointer();
		pplnDesc_.VS.BytecodeLength = shdrs.vsBlob_.Get()->GetBufferSize();
		pplnDesc_.PS.pShaderBytecode = shdrs.psBlob_.Get()->GetBufferPointer();
		pplnDesc_.PS.BytecodeLength = shdrs.psBlob_.Get()->GetBufferSize();

		// ���X�^���C�U�̐ݒ�
		pplnDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // �w�ʂ��J�����O���Ȃ�

		// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
		pplnDesc_.DepthStencilState.DepthEnable = false; // �[�x�e�X�g���Ȃ�
		pplnDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // ��ɏ㏑��

		// �}�`�̌`��ݒ�
		pplnDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	}

	// �v���~�e�B�u�`��̐ݒ�
	primitive_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // �O�p�`�X�g���b�v
}

void SpriteCommon::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.pTexManager_);
	pTexManager_ = state.pTexManager_;
	projection_ = YMath::MatOrthoGraphic();
	std::unique_ptr<PipelineSet::IStatus> pplnState = std::make_unique<PipelineSetStatus>();
	pplnSet_.Initialize(pplnState.get(), state.rootParams_);
}

void SpriteCommon::StaticSetDrawCommand()
{
	pplnSet_.SetDrawCommand();
}
