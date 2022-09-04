#include "ScissorRect.h"
#include <assert.h>

using DX::ScissorRect;

ID3D12GraphicsCommandList* ScissorRect::pCmdList = nullptr;

void ScissorRect::StaticInit(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList != nullptr);
	pCmdList = pCommandList;
}

void ScissorRect::Set(const SetStatus& set)
{
	// �V�U�[��`
	scissorRect.left	 = (LONG)set.topLeft.x;     // �؂蔲�����W ��
	scissorRect.top		 = (LONG)set.topLeft.y;     // �؂蔲�����W ��
	scissorRect.right	 = (LONG)set.bottomRight.x; // �؂蔲�����W �E
	scissorRect.bottom	 = (LONG)set.bottomRight.y; // �؂蔲�����W ��
}

void ScissorRect::Stack()
{
	// �V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	pCmdList->RSSetScissorRects(1, &scissorRect);
}
