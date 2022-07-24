#include "DXCommandQueue.h"
#include "DXDevice.h"
#include "Result.h"

void DXCommandQueue::Create()
{
	DXDevice* dev = DXDevice::GetInstance();
	Result::Check(dev->Device()->
		CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue)));
}

ID3D12CommandQueue* DXCommandQueue::Queue()
{
	return commandQueue;
}
