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
	// ビューポート設定
	viewport_.Width    = bottomRight.x_ - topLeft.x_; // 横幅
	viewport_.Height   = bottomRight.y_ - topLeft.y_; // 縦幅
	viewport_.TopLeftX = topLeft.x_; // 左上 X
	viewport_.TopLeftY = topLeft.y_; // 左上 Y
	viewport_.MinDepth = 0; // 縮小深度 (0 でいい)
	viewport_.MaxDepth = 1; // 拡大深度 (1 でいい)

	// シザー矩形設定
	scissorRect_.left	 = (LONG)topLeft.x_;     // 切り抜き座標 左
	scissorRect_.top	 = (LONG)topLeft.y_;     // 切り抜き座標 上
	scissorRect_.right	 = (LONG)bottomRight.x_; // 切り抜き座標 右
	scissorRect_.bottom	 = (LONG)bottomRight.y_; // 切り抜き座標 下
}

void ScreenDesc::SetDrawCommand() 
{
	// ビューポート設定コマンド
	pCmdList_->RSSetViewports(1, &viewport_);
	// シザー矩形設定コマンド
	pCmdList_->RSSetScissorRects(1, &scissorRect_);
}