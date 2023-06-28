#include "ScreenDesc.h"
#include <assert.h>

using YDX::ScreenDesc;
using YMath::Vector2;

ID3D12GraphicsCommandList* ScreenDesc::spCmdList_ = nullptr;

void ScreenDesc::StaticInitialize(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList);
	spCmdList_ = pCommandList;
}

void ScreenDesc::Initialize(const Vector2& topLeft, const Vector2& bottomRight, const size_t descNum)
{
	// �T�C�Y�ύX
	viewport_.resize(descNum);
	scissorRect_.resize(descNum);

	for (size_t i = 0; i < descNum; i++)
	{
		// �r���[�|�[�g�ݒ�
		viewport_[i].Width = bottomRight.x_ - topLeft.x_; // ����
		viewport_[i].Height = bottomRight.y_ - topLeft.y_; // �c��
		viewport_[i].TopLeftX = topLeft.x_; // ���� X
		viewport_[i].TopLeftY = topLeft.y_; // ���� Y
		viewport_[i].MinDepth = 0; // �k���[�x (0 �ł���)
		viewport_[i].MaxDepth = 1; // �g��[�x (1 �ł���)

		// �V�U�[��`�ݒ�
		scissorRect_[i].left = (LONG)topLeft.x_;     // �؂蔲�����W ��
		scissorRect_[i].top = (LONG)topLeft.y_;     // �؂蔲�����W ��
		scissorRect_[i].right = (LONG)bottomRight.x_; // �؂蔲�����W �E
		scissorRect_[i].bottom = (LONG)bottomRight.y_; // �؂蔲�����W ��
	}
}

void ScreenDesc::SetDrawCommand()
{
	// �r���[�|�[�g�ݒ�R�}���h
	spCmdList_->RSSetViewports(static_cast<UINT>(viewport_.size()), viewport_.data());
	// �V�U�[��`�ݒ�R�}���h
	spCmdList_->RSSetScissorRects(static_cast<UINT>(scissorRect_.size()), scissorRect_.data());
}