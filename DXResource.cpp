#include "DXResource.h"
#include "DXDevice.h"
#include "Result.h"

void DXResource::Create(const DXResourceInfo& rscInfo)
{
	DXDevice* dev = DXDevice::GetInstance();

	Result::Check(dev->Device()->
		CreateCommittedResource(
			&rscInfo.heapProp, // �q�[�v�ݒ�
			D3D12_HEAP_FLAG_NONE,
			&rscInfo.resDesc, // ���\�[�X�ݒ�
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&buff)));
}
