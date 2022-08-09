#include "DXViewport.h"

void DXViewport::Set(const SetStatus& set)
{
	// �r���[�|�[�g�ݒ�R�}���h
	viewport.Width = set.size.x; // ����
	viewport.Height = set.size.y; // �c��
	viewport.TopLeftX = set.topLeft.x; // ���� X
	viewport.TopLeftY = set.topLeft.y; // ���� Y
	viewport.MinDepth = set.minDepth; // �k���[�x (0 �ł���)
	viewport.MaxDepth = set.maxDepth; // �g��[�x (1 �ł���)

	cmdList = DXCommandList::GetInstance();
}

void DXViewport::Stack()
{
	// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	cmdList->List()->RSSetViewports(1, &viewport);
}
