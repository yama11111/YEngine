#include "CommandQueue.h"
#include "Device.h"
#include "Utility/Result.h"

using DX::CommandQueue;

void CommandQueue::Create()
{
	Device* dev = Device::GetInstance();

	//コマンドキュー設定
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	Utility::Result::Check(dev->Get()->
		CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue)));
}

ID3D12CommandQueue* CommandQueue::Get()
{
	return commandQueue.Get();
}
