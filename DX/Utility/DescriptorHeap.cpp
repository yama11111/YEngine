#include "DescriptorHeap.h"
#include "Device.h"
#include "Result.h"

using DX::Utility::DescriptorHeap;

void DescriptorHeap::Create()
{
	Device* dev = Device::GetInstance();
	Result::Check(dev->Get()->
		CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap)));
}

ID3D12DescriptorHeap* DescriptorHeap::Get()
{
	return heap.Get();
}

