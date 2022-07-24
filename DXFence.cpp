#include "DXFence.h"
#include "DXDevice.h"
#include "Result.h"

void DXFence::Create()
{
	DXDevice* dev = DXDevice::GetInstance();
	Result::Check(dev->Device()->
		CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)));
}

bool DXFence::ConfirmCommandComplate(ID3D12CommandQueue* commandQueue)
{
	// コマンドの実行完了を待つ
	commandQueue->Signal(fence, ++fenceVal);
	if (fence->GetCompletedValue() != fenceVal)
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence->SetEventOnCompletion(fenceVal, event);
		if (event == 0) return false;
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}
	return true;
}
