#include "PipelineSet.h"
#include "VertexLayoutManager.h"
#include <assert.h>

using DX::PipelineSet;
using DX::PipelineState;

ID3D12GraphicsCommandList* PipelineSet::pCmdList = nullptr;

void PipelineSet::StaticInit(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList != nullptr);
	pCmdList = pCommandList;
}

void PipelineSet::Create(const int dimension)
{
	VertexLayoutManager* layout = VertexLayoutManager::GetInstance();

	switch (dimension)
	{
	case PipelineState::Dimension::Two:
		shdrs.Load2D();
		rootSig.Create(shdrs.errorBlob);
		pplnState.Create(rootSig.Get(), shdrs, layout->spriteIL, PipelineState::Dimension::Two);
		d = PipelineState::Dimension::Two;
		break;
	case PipelineState::Dimension::Three:
		shdrs.Load3D();
		rootSig.Create(shdrs.errorBlob);
		pplnState.Create(rootSig.Get(), shdrs, layout->modelIL, PipelineState::Dimension::Three);
		d = PipelineState::Dimension::Three;
		break;
	default:
		assert(false);
		break;
	}
}

void PipelineSet::SetCommand()
{
	// �p�C�v���C���X�e�[�g�̐ݒ�R�}���h
	pCmdList->SetPipelineState(pplnState.Get());

	// ���[�g�V�O�l�`���̐ݒ�R�}���h
	pCmdList->SetGraphicsRootSignature(rootSig.Get());
	switch (d)
	{
	case PipelineState::Dimension::Two:
		// �v���~�e�B�u�`��̐ݒ�R�}���h
		pCmdList->IASetPrimitiveTopology(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); // �O�p�`�X�g���b�v
		break;
	case PipelineState::Dimension::Three:
		// �v���~�e�B�u�`��̐ݒ�R�}���h
		pCmdList->IASetPrimitiveTopology(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
		break;
	}
}
