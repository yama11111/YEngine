#include "DXScissorRect.h"

void DXScissorRect::Set(const SetStatus& set)
{
	// �V�U�[��`
	scissorRect.left = set.topLeft.x;     // �؂蔲�����W ��
	scissorRect.top = set.topLeft.y;     // �؂蔲�����W ��
	scissorRect.right = set.bottomRight.x; // �؂蔲�����W �E
	scissorRect.bottom = set.bottomRight.y; // �؂蔲�����W ��

	cmdList = DXCommandList::GetInstance();
}

void DXScissorRect::Stack()
{
	// �V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	cmdList->List()->RSSetScissorRects(1, &scissorRect);
}
