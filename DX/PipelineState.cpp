#include "PipelineState.h"
#include "Utility/Result.h"

using DX::PipelineState;
using DX::Utility::Result;

DX::Device* PipelineState::dev = nullptr;

PipelineState::PipelineState() :
	blendDesc(desc.BlendState.RenderTarget[0])
{
}

void DX::PipelineState::StaticInit()
{
	dev = Device::GetInstance();
}

void DX::PipelineState::Create(ID3D12RootSignature* rootSignature, ShaderSet& shaders,
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout, const int dimension)
{
	// �V�F�[�_�[�̐ݒ�
	desc.VS.pShaderBytecode = shaders.vsBlob->GetBufferPointer();
	desc.VS.BytecodeLength = shaders.vsBlob->GetBufferSize();
	desc.PS.pShaderBytecode = shaders.psBlob->GetBufferPointer();
	desc.PS.BytecodeLength = shaders.psBlob->GetBufferSize();

	// �T���v���}�X�N�̐ݒ�
	desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

	// ���X�^���C�U�̐ݒ�
	desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // �w�ʂ��J�����O���Ȃ�
	desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
	desc.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����

	// �u�����h�X�e�[�g
	blendDesc = desc.BlendState.RenderTarget[0];
	blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA�S�Ẵ`�����l����`��

	blendDesc.BlendEnable = true;                // �u�����h��L���ɂ���
	blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD; // ���Z
	blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;   // �\�[�X�̒l��100%�g��
	blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO; // �f�X�g�̒l��  0%�g��

	// ����������
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // ���Z
	blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;      // �\�[�X�̃A���t�@�l
	blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - �\�[�X�̃A���t�@�l

	// ���_���C�A�E�g�̐ݒ�
	desc.InputLayout.pInputElementDescs = inputLayout.data();
	desc.InputLayout.NumElements = (UINT)inputLayout.size();
	// �}�`�̌`��ݒ�
	desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// ���̑��̐ݒ�
	desc.NumRenderTargets = 1; // �`��Ώۂ�1��
	desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255�w���RGBA
	desc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	desc.pRootSignature = rootSignature;

	switch (dimension)
	{
	case Two:
		// ���X�^���C�U�̐ݒ�
		desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // �w�ʂ��J�����O���Ȃ�

		// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
		desc.DepthStencilState.DepthEnable = false; // �[�x�e�X�g���Ȃ�
		desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // ��ɏ㏑��
		break;
	case Three:
		// ���X�^���C�U�̐ݒ�
		desc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // �w�ʂ��J�����O

		// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
		desc.DepthStencilState.DepthEnable = true; // �[�x�e�X�g
		desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // �������݋���
		desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // ��������΍��i
		desc.DSVFormat = DXGI_FORMAT_D32_FLOAT; // �[�x�t�H�[�}�b�g
		break;
	default:
		Result::Assert(false);
		return;
		break;
	}

	// �p�C�v�����X�e�[�g�̐���
	CreateState();
}

void PipelineState::ChangeSolid()
{
	// �|���S�����h��Ԃ�
	desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	CreateState();
}
void PipelineState::ChangeWire()
{
	// ���C���[�t���[��
	desc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	CreateState();
}

void PipelineState::SetBlendAdd()
{
	// ���Z����
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // ���Z
	blendDesc.SrcBlend = D3D12_BLEND_ONE;   // �\�[�X�̒l��100%�g��
	blendDesc.DestBlend = D3D12_BLEND_ONE;  // �f�X�g�̒l��100%�g��
	CreateState();
}
void PipelineState::SetBlendSub()
{
	// ���Z����
	blendDesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT; // ���Z(�f�X�g - �\�[�X)
	blendDesc.SrcBlend = D3D12_BLEND_ONE;   // �\�[�X�̒l��100%�g��
	blendDesc.DestBlend = D3D12_BLEND_ONE;  // �f�X�g�̒l��100%�g��
	CreateState();
}
void PipelineState::SetBlendInversion()
{
	// �F���]
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // ���Z
	blendDesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR; // 1.0f - �f�X�g�J���[�̒l
	blendDesc.DestBlend = D3D12_BLEND_ZERO;          // �f�X�g�̒l��  0%�g��
	CreateState();
}
void PipelineState::SetBlendAlpha()
{
	// ����������
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // ���Z
	blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;      // �\�[�X�̃A���t�@�l
	blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - �\�[�X�̃A���t�@�l
	CreateState();
}

ID3D12PipelineState* DX::PipelineState::Get()
{
	return pplnState.Get();
}

void PipelineState::CreateState()
{
	// �p�C�v�����X�e�[�g�̐���
	Result::Check(dev->Get()->
		CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(&pplnState)));
}
