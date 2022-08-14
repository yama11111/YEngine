#include "DXDescriptorHeap.h"
#include "DXDevice.h"
#include "Result.h"

void DXDescriptorHeap::Create()
{
	DXDevice* dev = DXDevice::GetInstance();
	Result::Check(dev->Device()->
		CreateDescriptorHeap(&hDesc, IID_PPV_ARGS(&heap)));
}
