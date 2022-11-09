#include "GPUResource.h"
#include "YAssert.h"

using DX::GPUResource;

ID3D12Device* GPUResource::pDevice_ = nullptr;

void GPUResource::StaticInitialize(ID3D12Device* pDevice)
{
	assert(pDevice);
	pDevice_ = pDevice;
}

void GPUResource::Create(const CreateStatus& state)
{
	Result(pDevice_->CreateCommittedResource(
		&state.heapProp_, // �q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&state.resDesc_, // ���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&buffer_)));
}
