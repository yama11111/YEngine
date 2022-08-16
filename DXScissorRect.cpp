#include "DXScissorRect.h"

void DXScissorRect::Set(const SetStatus& set)
{
	// シザー矩形
	scissorRect.left	 = (LONG)set.topLeft.x;     // 切り抜き座標 左
	scissorRect.top		 = (LONG)set.topLeft.y;     // 切り抜き座標 上
	scissorRect.right	 = (LONG)set.bottomRight.x; // 切り抜き座標 右
	scissorRect.bottom	 = (LONG)set.bottomRight.y; // 切り抜き座標 下

	cmdList = DXCommandList::GetInstance();
}

void DXScissorRect::Stack()
{
	// シザー矩形設定コマンドを、コマンドリストに積む
	cmdList->List()->RSSetScissorRects(1, &scissorRect);
}
