#include "DXPipelineState.h"
#include "Result.h"

DXPipelineState::DXPipelineState() :
	blendDesc(pipelineDesc.BlendState.RenderTarget[0])
{
}

void DXPipelineState::Create(ID3D12RootSignature* rootSignature, 
	DXShaderManager& shaderM, std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout)
{
	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	// �V�F�[�_�[�̐ݒ�
	pipelineDesc.VS.pShaderBytecode = shaderM.vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = shaderM.vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = shaderM.psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = shaderM.psBlob->GetBufferSize();

	// �T���v���}�X�N�̐ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

	// ���X�^���C�U�̐ݒ�
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // �w�ʂ��J�����O
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
	pipelineDesc.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����

	// �u�����h�X�e�[�g
	blendDesc = pipelineDesc.BlendState.RenderTarget[0];
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
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout.data();
	pipelineDesc.InputLayout.NumElements = (UINT)inputLayout.size();
	// �}�`�̌`��ݒ�
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// ���̑��̐ݒ�
	pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ�1��
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255�w���RGBA
	pipelineDesc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = rootSignature;

	//// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
	//pipelineDesc.DepthStencilState.DepthEnable = true; // �[�x�e�X�g
	//pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // �������݋���
	//pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // ��������΍��i
	//pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT; // �[�x�t�H�[�}�b�g

	dev = DXDevice::GetInstance();

	// �p�C�v�����X�e�[�g�̐���
	CreateState();
}

void DXPipelineState::ChangeSolid()
{
	// �|���S�����h��Ԃ�
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	CreateState();
}

void DXPipelineState::ChangeWire()
{
	// ���C���[�t���[��
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	CreateState();
}

void DXPipelineState::SetBlendAdd()
{
	// ���Z����
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // ���Z
	blendDesc.SrcBlend = D3D12_BLEND_ONE;   // �\�[�X�̒l��100%�g��
	blendDesc.DestBlend = D3D12_BLEND_ONE;  // �f�X�g�̒l��100%�g��
	CreateState();
}

void DXPipelineState::SetBlendSub()
{
	// ���Z����
	blendDesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT; // ���Z(�f�X�g - �\�[�X)
	blendDesc.SrcBlend = D3D12_BLEND_ONE;   // �\�[�X�̒l��100%�g��
	blendDesc.DestBlend = D3D12_BLEND_ONE;  // �f�X�g�̒l��100%�g��
	CreateState();
}

void DXPipelineState::SetBlendInversion()
{
	// �F���]
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // ���Z
	blendDesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR; // 1.0f - �f�X�g�J���[�̒l
	blendDesc.DestBlend = D3D12_BLEND_ZERO;          // �f�X�g�̒l��  0%�g��
	CreateState();
}

void DXPipelineState::SetBlendAlpha()
{
	// ����������
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // ���Z
	blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;      // �\�[�X�̃A���t�@�l
	blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - �\�[�X�̃A���t�@�l
	CreateState();
}

void DXPipelineState::CreateState()
{
	// �p�C�v�����X�e�[�g�̐���
	Result::Check(dev->Device()->
		CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState)));
}
