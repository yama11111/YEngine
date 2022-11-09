#include "ScreenDesc.h"
#include <assert.h>

using DX::ScreenDesc;

ID3D12GraphicsCommandList* ScreenDesc::pCmdList_ = nullptr;

void ScreenDesc::StaticInitialize(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList);
	pCmdList_ = pCommandList;
}

void ScreenDesc::Initialize(const Math::Vec2& topLeft, const Math::Vec2& bottomRight)
{
	// �r���[�|�[�g�ݒ�
	viewport_.Width    = bottomRight.x_ - topLeft.x_; // ����
	viewport_.Height   = bottomRight.y_ - topLeft.y_; // �c��
	viewport_.TopLeftX = topLeft.x_; // ���� X
	viewport_.TopLeftY = topLeft.y_; // ���� Y
	viewport_.MinDepth = 0; // �k���[�x (0 �ł���)
	viewport_.MaxDepth = 1; // �g��[�x (1 �ł���)

	// �V�U�[��`�ݒ�
	scissorRect_.left	 = (LONG)topLeft.x_;     // �؂蔲�����W ��
	scissorRect_.top	 = (LONG)topLeft.y_;     // �؂蔲�����W ��
	scissorRect_.right	 = (LONG)bottomRight.x_; // �؂蔲�����W �E
	scissorRect_.bottom	 = (LONG)bottomRight.y_; // �؂蔲�����W ��
}

void ScreenDesc::SetDrawCommand() 
{
	// �r���[�|�[�g�ݒ�R�}���h
	pCmdList_->RSSetViewports(1, &viewport_);
	// �V�U�[��`�ݒ�R�}���h
	pCmdList_->RSSetScissorRects(1, &scissorRect_);
}