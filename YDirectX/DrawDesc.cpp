#include "DrawDesc.h"
#include "../Def.h"

using DX::DrawDesc;

void DrawDesc::Set()
{
	viewport.Set({ WIN_SIZE });
	scissorRect.Set({ { 0, 0 }, WIN_SIZE });
}

void DrawDesc::SetCommand()
{
	// ビューポート設定コマンドを、コマンドリストに積む
	viewport.Stack();
	// シザー矩形設定コマンドを、コマンドリストに積む
	scissorRect.Stack();
}
