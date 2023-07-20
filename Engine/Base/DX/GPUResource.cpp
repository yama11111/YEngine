#include "GPUResource.h"
#include "YAssert.h"

#pragma comment(lib, "d3d12.lib")

using YDX::GPUResource;

ID3D12Device* GPUResource::spDevice_ = nullptr;

void GPUResource::Create(
	const D3D12_HEAP_PROPERTIES* pHeapProp, 
	const D3D12_RESOURCE_DESC* pResourceDesc, 
	const D3D12_RESOURCE_STATES resourceState, 
	const D3D12_CLEAR_VALUE* pClearValue)
{
	Result(spDevice_->CreateCommittedResource(
		pHeapProp,
		D3D12_HEAP_FLAG_NONE,
		pResourceDesc,
		resourceState,
		pClearValue,
		IID_PPV_ARGS(&buffer_)));
}

void GPUResource::StaticInitialize(ID3D12Device* pDevice)
{
	assert(pDevice);
	spDevice_ = pDevice;
}
