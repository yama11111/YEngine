#include "PipelineSet.h"
#include "YAssert.h"
#include <memory>

using YDX::PipelineSet;

ID3D12Device* PipelineSet::spDevice_ = nullptr;
ID3D12GraphicsCommandList* PipelineSet::spCmdList_ = nullptr;

void PipelineSet::StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList)
{
	assert(pDevice);
	assert(pCommandList);

	spDevice_ = pDevice;
	spCmdList_ = pCommandList;
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
	Result(spDevice_->CreateRootSignature(
		0,
		rootSigBlob->GetBufferPointer(),
		rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature_)));
}

void PipelineSet::CreatePipelineState(D3D12_GRAPHICS_PIPELINE_STATE_DESC& pipelineDesc)
{
	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = rootSignature_.Get();

	// �p�C�v�����X�e�[�g�̐���
	Result(spDevice_->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState_)));
}

void PipelineSet::SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitive)
{
	// ����`�Ȃ�e��
	assert(primitive != D3D_PRIMITIVE_TOPOLOGY_UNDEFINED);

	// ���
	primitive_ = primitive;
}

void PipelineSet::Initialize(
	const std::vector<D3D12_STATIC_SAMPLER_DESC>& samplerDescs,
	const std::vector<D3D12_ROOT_PARAMETER>& rootParams,
	D3D12_GRAPHICS_PIPELINE_STATE_DESC& pipelineDesc,
	const D3D_PRIMITIVE_TOPOLOGY& primitive)
{
	// ���[�g�V�O�l�`������
	CreateRootSignature(rootParams, samplerDescs);

	// �p�C�v���C���X�e�[�g����
	CreatePipelineState(pipelineDesc);

	// �v���~�e�B�u�`��ݒ�
	SetPrimitiveTopology(primitive);
}

void PipelineSet::SetDrawCommand()
{
	// �p�C�v���C���X�e�[�g�̐ݒ�R�}���h
	spCmdList_->SetPipelineState(pipelineState_.Get());

	// ���[�g�V�O�l�`���̐ݒ�R�}���h
	spCmdList_->SetGraphicsRootSignature(rootSignature_.Get());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	spCmdList_->IASetPrimitiveTopology(primitive_);
}
