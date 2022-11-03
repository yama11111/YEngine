#include "ScreenDesc.h"
#include <assert.h>

using DX::ScreenDesc;

ID3D12GraphicsCommandList* ScreenDesc::pCmdList_ = nullptr;

void ScreenDesc::StaticInitialize(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList != nullptr);
	pCmdList_ = pCommandList;
}

void ScreenDesc::Initialize(const Math::Vec2& topLeft, const Math::Vec2& bottomRight)
{
	// ビューポート設定
	viewport_.Width    = bottomRight.x - topLeft.x; // 横幅
	viewport_.Height   = bottomRight.y - topLeft.y; // 縦幅
	viewport_.TopLeftX = topLeft.x; // 左上 X
	viewport_.TopLeftY = topLeft.y; // 左上 Y
	viewport_.MinDepth = 0; // 縮小深度 (0 でいい)
	viewport_.MaxDepth = 1; // 拡大深度 (1 でいい)

	// シザー矩形設定
	scissorRect_.left	 = (LONG)topLeft.x;     // 切り抜き座標 左
	scissorRect_.top	 = (LONG)topLeft.y;     // 切り抜き座標 上
	scissorRect_.right	 = (LONG)bottomRight.x; // 切り抜き座標 右
	scissorRect_.bottom	 = (LONG)bottomRight.y; // 切り抜き座標 下
}

void ScreenDesc::SetCommand() 
{
	// ビューポート設定コマンド
	pCmdList_->RSSetViewports(1, &viewport_);
	// シザー矩形設定コマンド
	pCmdList_->RSSetScissorRects(1, &scissorRect_);
}