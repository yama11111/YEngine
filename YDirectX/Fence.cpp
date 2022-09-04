#include "Fence.h"
#include "Device.h"
#include "Utility/Result.h"

using DX::Fence;

void Fence::Create()
{
	Device* dev = Device::GetInstance();
	Utility::Result::Check(dev->Get()->
		CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)));
}

bool Fence::ConfirmCommandComplate(ID3D12CommandQueue* commandQueue)
{
	// コマンドの実行完了を待つ
	commandQueue->Signal(fence.Get(), ++fenceVal);
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
