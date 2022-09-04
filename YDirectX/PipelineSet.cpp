#include "PipelineSet.h"
#include "VertexLayoutManager.h"
#include <assert.h>

using DX::PipelineSet;

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
	case Two:
		shdrM.Load2D();
		rootSig.Create(shdrM.errorBlob);
		pplnState.Create2D(rootSig.Get(), shdrM, layout->spriteIL);
		d = Two;
		break;
	case Three:
		shdrM.Load3D();
		rootSig.Create(shdrM.errorBlob);
		pplnState.Create3D(rootSig.Get(), shdrM, layout->modelIL);
		d = Three;
		break;
	default:
		assert(false);
		break;
	}
}

void PipelineSet::SetCommand()
{
	// �p�C�v���C���X�e�[�g�̐ݒ�R�}���h
	pCmdList->SetPipelineState(pplnState.pplnState);

	// ���[�g�V�O�l�`���̐ݒ�R�}���h
	pCmdList->SetGraphicsRootSignature(rootSig.Get());
	switch (d)
	{
	case Two:
		// �v���~�e�B�u�`��̐ݒ�R�}���h
		pCmdList->IASetPrimitiveTopology(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); // �O�p�`�X�g���b�v
		break;
	case Three:
		// �v���~�e�B�u�`��̐ݒ�R�}���h
		pCmdList->IASetPrimitiveTopology(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
		break;
	}
}
