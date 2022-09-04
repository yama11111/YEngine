#include "ScissorRect.h"
#include <assert.h>

using DX::ScissorRect;

ID3D12GraphicsCommandList* ScissorRect::pCmdList = nullptr;

void ScissorRect::StaticInit(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList != nullptr);
	pCmdList = pCommandList;
}

void ScissorRect::Set(const SetStatus& set)
{
	// シザー矩形
	scissorRect.left	 = (LONG)set.topLeft.x;     // 切り抜き座標 左
	scissorRect.top		 = (LONG)set.topLeft.y;     // 切り抜き座標 上
	scissorRect.right	 = (LONG)set.bottomRight.x; // 切り抜き座標 右
	scissorRect.bottom	 = (LONG)set.bottomRight.y; // 切り抜き座標 下
}

void ScissorRect::Stack()
{
	// シザー矩形設定コマンドを、コマンドリストに積む
	pCmdList->RSSetScissorRects(1, &scissorRect);
}
