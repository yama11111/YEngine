#include "DXResource.h"
#include "DXDevice.h"
#include "Result.h"

void DXResource::Create(const DXResourceInfo& rscInfo)
{
	DXDevice* dev = DXDevice::GetInstance();

	Result::Check(dev->Device()->
		CreateCommittedResource(
			&rscInfo.heapProp, // ヒープ設定
			D3D12_HEAP_FLAG_NONE,
			&rscInfo.resDesc, // リソース設定
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&buff)));
}

void DXResource::Create(const DXResourceInfo2& rscInfo)
{
	DXDevice* dev = DXDevice::GetInstance();

	Result::Check(dev->Device()->
		CreateCommittedResource(
			&rscInfo.heapProp, // ヒープ設定
			D3D12_HEAP_FLAG_NONE,
			&rscInfo.resDesc, // リソース設定
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&rscInfo.clearValue,
			IID_PPV_ARGS(&buff)));
}
