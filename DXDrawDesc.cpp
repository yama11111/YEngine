#include "DXDrawDesc.h"
#include "Def.h"

void DXDrawDesc::Set()
{
	viewport.Set({ WIN_SIZE });
	scissorRect.Set({ { 0, 0 }, WIN_SIZE });
}

void DXDrawDesc::SetCommand()
{
	// ビューポート設定コマンドを、コマンドリストに積む
	viewport.Stack();
	// シザー矩形設定コマンドを、コマンドリストに積む
	scissorRect.Stack();
}
