#include "Viewport.h"
#include <assert.h>

using DX::Viewport;

ID3D12GraphicsCommandList* Viewport::pCmdList = nullptr;

void Viewport::StaticInit(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList != nullptr);
	pCmdList = pCommandList;
}

void Viewport::Set(const SetStatus& set)
{
	// �r���[�|�[�g�ݒ�R�}���h
	viewport.Width    = set.size.x; // ����
	viewport.Height   = set.size.y; // �c��
	viewport.TopLeftX = set.topLeft.x; // ���� X
	viewport.TopLeftY = set.topLeft.y; // ���� Y
	viewport.MinDepth = set.minDepth; // �k���[�x (0 �ł���)
	viewport.MaxDepth = set.maxDepth; // �g��[�x (1 �ł���)
}

void Viewport::Stack()
{
	// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	pCmdList->RSSetViewports(1, &viewport);
}
