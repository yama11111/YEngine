#include "PipelineSet.h"
#include "YAssert.h"
#include <memory>

using YDX::PipelineSet;

ID3D12Device* PipelineSet::pDevice_ = nullptr;
ID3D12GraphicsCommandList* PipelineSet::pCmdList_ = nullptr;

void PipelineSet::StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList)
{
	assert(pDevice);
	assert(pCommandList);

	pDevice_ = pDevice;
	pCmdList_ = pCommandList;
}

void PipelineSet::CreateRootSignature(
	const std::vector<D3D12_ROOT_PARAMETER>& rootParams, 
	const std::vector<D3D12_STATIC_SAMPLER_DESC>& samplerDescs)
{
	// �G���[�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	// ���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rsDesc{};
	rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rsDesc.pParameters = rootParams.data();					 // ���[�g�p�����[�^�̐擪�A�h���X
	rsDesc.NumParameters = (UINT)rootParams.size();			 // ���[�g�p�����[�^��
	rsDesc.pStaticSamplers = samplerDescs.data();			 // �e�N�X�`���T���v���[�̐擪�A�h���X
	rsDesc.NumStaticSamplers = (UINT)samplerDescs.size();	 // �e�N�X�`���T���v���[��

	// ���[�g�V�O�l�`���̃V���A���C�Y
	Microsoft::WRL::ComPtr<ID3DBlob> rootSigBlob = nullptr; // ���[�g�V�O�l�`���I�u�W�F�N�g
	Result(D3D12SerializeRootSignature(&rsDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, errorBlob.GetAddressOf()));

	// ���[�g�V�O�l�`���̐���
	Result(pDevice_->CreateRootSignature(
		0,
		rootSigBlob->GetBufferPointer(),
		rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature_)));
}

void PipelineSet::CreatePipelineState(
	D3D12_GRAPHICS_PIPELINE_STATE_DESC& pipelineDesc, 
	const std::vector<D3D12_INPUT_ELEMENT_DESC>& inputLayout)
{
	// �T���v���}�X�N�̐ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

	// ���X�^���C�U�̐ݒ�
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
	pipelineDesc.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����

	// �u�����h�X�e�[�g
	D3D12_RENDER_TARGET_BLEND_DESC& blendDesc = pipelineDesc.BlendState.RenderTarget[0];
	blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA�S�Ẵ`�����l����`��

	blendDesc.BlendEnable = true;                // �u�����h��L���ɂ���
	blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD; // ���Z
	blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;   // �\�[�X�̒l��100%�g��
	blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO; // �f�X�g�̒l��  0%�g��

	// ����������
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD;			 // ���Z
	blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;      // �\�[�X�̃A���t�@�l
	blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - �\�[�X�̃A���t�@�l

	// ���_���C�A�E�g�̐ݒ�
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout.data(); // ���_���C�A�E�g�̐擪�A�h���X
	pipelineDesc.InputLayout.NumElements = (UINT)inputLayout.size(); // ���_���C�A�E�g��

	// ���̑��̐ݒ�
	pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ�1��
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255�w���RGBA
	pipelineDesc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = rootSignature_.Get();

	// �p�C�v�����X�e�[�g�̐���
	Result(pDevice_->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState_)));
}

void PipelineSet::SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitive)
{
	// ����`�Ȃ�e��
	assert(primitive != D3D_PRIMITIVE_TOPOLOGY_UNDEFINED);

	// ���
	primitive_ = primitive;
}

void PipelineSet::Initialize(InitStatus& status)
{
	// ���[�g�V�O�l�`������
	CreateRootSignature(status.rootParams_, status.samplerDescs_);

	// �p�C�v���C���X�e�[�g����
	CreatePipelineState(status.pipelineDesc_, status.inputLayout_);

	// �v���~�e�B�u�`��ݒ�
	SetPrimitiveTopology(status.primitive_);
}

void PipelineSet::SetDrawCommand()
{
	// �p�C�v���C���X�e�[�g�̐ݒ�R�}���h
	pCmdList_->SetPipelineState(pipelineState_.Get());

	// ���[�g�V�O�l�`���̐ݒ�R�}���h
	pCmdList_->SetGraphicsRootSignature(rootSignature_.Get());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	pCmdList_->IASetPrimitiveTopology(primitive_);
}
