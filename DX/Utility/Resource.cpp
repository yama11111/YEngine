#include "Resource.h"
#include "Device.h"
#include "Result.h"

using DX::Utility::Resource;

void Resource::Create(const ResourceInfo& rscInfo)
{
	Device* dev = Device::GetInstance();

	Result::Check(dev->Get()->
		CreateCommittedResource(
			&rscInfo.heapProp, // ヒープ設定
			D3D12_HEAP_FLAG_NONE,
			&rscInfo.resDesc, // リソース設定
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&buffer)));
}

void Resource::Create(const ResourceInfo2& rscInfo)
{
	Device* dev = Device::GetInstance();

	Result::Check(dev->Get()->
		CreateCommittedResource(
			&rscInfo.heapProp, // ヒープ設定
			D3D12_HEAP_FLAG_NONE,
			&rscInfo.resDesc, // リソース設定
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&rscInfo.clearValue,
			IID_PPV_ARGS(&buffer)));
}

ID3D12Resource* Resource::Get()
{
	return buffer.Get();
}
