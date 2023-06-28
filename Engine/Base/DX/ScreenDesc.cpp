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
	// サイズ変更
	viewport_.resize(descNum);
	scissorRect_.resize(descNum);

	for (size_t i = 0; i < descNum; i++)
	{
		// ビューポート設定
		viewport_[i].Width = bottomRight.x_ - topLeft.x_; // 横幅
		viewport_[i].Height = bottomRight.y_ - topLeft.y_; // 縦幅
		viewport_[i].TopLeftX = topLeft.x_; // 左上 X
		viewport_[i].TopLeftY = topLeft.y_; // 左上 Y
		viewport_[i].MinDepth = 0; // 縮小深度 (0 でいい)
		viewport_[i].MaxDepth = 1; // 拡大深度 (1 でいい)

		// シザー矩形設定
		scissorRect_[i].left = (LONG)topLeft.x_;     // 切り抜き座標 左
		scissorRect_[i].top = (LONG)topLeft.y_;     // 切り抜き座標 上
		scissorRect_[i].right = (LONG)bottomRight.x_; // 切り抜き座標 右
		scissorRect_[i].bottom = (LONG)bottomRight.y_; // 切り抜き座標 下
	}
}

void ScreenDesc::SetDrawCommand()
{
	// ビューポート設定コマンド
	spCmdList_->RSSetViewports(static_cast<UINT>(viewport_.size()), viewport_.data());
	// シザー矩形設定コマンド
	spCmdList_->RSSetScissorRects(static_cast<UINT>(scissorRect_.size()), scissorRect_.data());
}