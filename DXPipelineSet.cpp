#include "DXPipelineSet.h"

void DXPipelineSet::Create2D()
{
	cmdList = DXCommandList::GetInstance();
	DXVertexLayoutManager* layout = DXVertexLayoutManager::GetInstance();

	shdrM.Load2D();
	rootSig.Create(shdrM.errorBlob);
	pplnState.Create2D(rootSig.rootSignature, shdrM, layout->spriteIL);
}

void DXPipelineSet::Create3D()
{
	cmdList = DXCommandList::GetInstance();
	DXVertexLayoutManager* layout = DXVertexLayoutManager::GetInstance();

	shdrM.Load3D();
	rootSig.Create(shdrM.errorBlob);
	pplnState.Create3D(rootSig.rootSignature, shdrM, layout->modelIL);
}

void DXPipelineSet::SetCommand2D()
{
	// �p�C�v���C���X�e�[�g�̐ݒ�R�}���h
	cmdList->List()->SetPipelineState(pplnState.pipelineState);

	// ���[�g�V�O�l�`���̐ݒ�R�}���h
	cmdList->List()->SetGraphicsRootSignature(rootSig.rootSignature);

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->List()->IASetPrimitiveTopology(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); // �O�p�`�X�g���b�v
}

void DXPipelineSet::SetCommand3D()
{
	// �p�C�v���C���X�e�[�g�̐ݒ�R�}���h
	cmdList->List()->SetPipelineState(pplnState.pipelineState);

	// ���[�g�V�O�l�`���̐ݒ�R�}���h
	cmdList->List()->SetGraphicsRootSignature(rootSig.rootSignature);

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->List()->IASetPrimitiveTopology(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
}
