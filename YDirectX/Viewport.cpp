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
	// ビューポート設定コマンド
	viewport.Width    = set.size.x; // 横幅
	viewport.Height   = set.size.y; // 縦幅
	viewport.TopLeftX = set.topLeft.x; // 左上 X
	viewport.TopLeftY = set.topLeft.y; // 左上 Y
	viewport.MinDepth = set.minDepth; // 縮小深度 (0 でいい)
	viewport.MaxDepth = set.maxDepth; // 拡大深度 (1 でいい)
}

void Viewport::Stack()
{
	// ビューポート設定コマンドを、コマンドリストに積む
	pCmdList->RSSetViewports(1, &viewport);
}
