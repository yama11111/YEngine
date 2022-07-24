#include "DXResourceBarrier.h"
#include "DXCommandList.h"

void DXResourceBarrier::SetCurrentBackBuffer(ID3D12Resource* backBuffer)
{
	barrierDesc.Transition.pResource = backBuffer; // バックバッファを指定
}

bool DXResourceBarrier::ChangeState(const int state)
{
	switch (state)
	{
	case RenderTarget:
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;       // 表示 状態から
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;  // 描画 状態へ
		break;
	case Present:
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // 描画 状態から
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;        // 表示 状態へ
		break;
	default:
		return false;
		break;
	}

	DXCommandList* cmdList = DXCommandList::GetInstance();
	cmdList->List()->ResourceBarrier(1, &barrierDesc);

	return true;
}
