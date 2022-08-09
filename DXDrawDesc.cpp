#include "DXDrawDesc.h"
#include "Def.h"

void DXDrawDesc::Create()
{
	shdrM.Load();
	rootSig.Create(shdrM.errorBlob);
	pplnState.Create(rootSig.rootSignature, shdrM, layout.inputLayout);
	viewport.Set({ WIN_SIZE });
	scissorRect.Set({ { 0, 0 }, WIN_SIZE });

	cmdList = DXCommandList::GetInstance();
}

void DXDrawDesc::SetCommand()
{
	// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	viewport.Stack();
	// �V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	scissorRect.Stack();

	// �p�C�v���C���X�e�[�g�̐ݒ�R�}���h
	cmdList->List()->SetPipelineState(pplnState.pipelineState);

	// ���[�g�V�O�l�`���̐ݒ�R�}���h
	cmdList->List()->SetGraphicsRootSignature(rootSig.rootSignature);

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->List()->IASetPrimitiveTopology(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
}
