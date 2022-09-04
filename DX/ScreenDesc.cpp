#include "ScreenDesc.h"
#include "Def.h"

using DX::ScreenDesc;

void ScreenDesc::Set()
{
	viewport.Set({ WIN_SIZE });
	scissorRect.Set({ { 0, 0 }, WIN_SIZE });
}

void ScreenDesc::SetCommand()
{
	// ビューポート設定コマンドを、コマンドリストに積む
	viewport.Stack();
	// シザー矩形設定コマンドを、コマンドリストに積む
	scissorRect.Stack();
}
