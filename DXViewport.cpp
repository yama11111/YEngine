#include "DXViewport.h"

void DXViewport::Set(const SetStatus& set)
{
	// ビューポート設定コマンド
	viewport.Width = set.size.x; // 横幅
	viewport.Height = set.size.y; // 縦幅
	viewport.TopLeftX = set.topLeft.x; // 左上 X
	viewport.TopLeftY = set.topLeft.y; // 左上 Y
	viewport.MinDepth = set.minDepth; // 縮小深度 (0 でいい)
	viewport.MaxDepth = set.maxDepth; // 拡大深度 (1 でいい)

	cmdList = DXCommandList::GetInstance();
}

void DXViewport::Stack()
{
	// ビューポート設定コマンドを、コマンドリストに積む
	cmdList->List()->RSSetViewports(1, &viewport);
}
