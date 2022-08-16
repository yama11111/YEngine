#include "DXSRVHeap.h"
#include "DXDevice.h"
#include "DXRootParameterManager.h"

DXSRVHeap::DXSRVHeap()
{
	// SRV�̍ő��
	const size_t kMaxSRVCount = 2056;

	// �f�X�N���v�^�q�[�v�̐ݒ�
	srvHeap.hDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeap.hDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // �V�F�[�_�[���猩����悤��
	srvHeap.hDesc.NumDescriptors = kMaxSRVCount;

	// �ݒ�����Ƃ�SRV�p�f�X�N���v�^�q�[�v�𐶐�
	srvHeap.Create();

	// SRV�q�[�v�̐擪�n���h�����擾
	srvHandle = srvHeap.heap->GetCPUDescriptorHandleForHeapStart();

	DXDevice* dev = DXDevice::GetInstance();
	incrementSize = dev->Device()->
		GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	cmdList = DXCommandList::GetInstance();

	// �f�X�N���v�^�����W�̐ݒ�
	descriptorRange.NumDescriptors = 1; // 1�x�̕`��Ɏg���e�N�X�`����1���Ȃ̂�1
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0; // �e�N�X�`�����W�X�^0��
	descriptorRange.OffsetInDescriptorsFromTableStart =
		D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
}

UINT DXSRVHeap::SetSRV(ID3D12Resource* texBuff, D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc)
{
	DXDevice* dev = DXDevice::GetInstance();

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	dev->Device()->CreateShaderResourceView(texBuff, &srvDesc, srvHandle);

	// ��n���h����i�߂�
	srvHandle.ptr += incrementSize;

	UINT result = index;
	index++;

	return result;
}

void DXSRVHeap::SetDescriptorHeaps()
{
	// SRV�q�[�v�̐ݒ�R�}���h
	cmdList->List()->SetDescriptorHeaps(1, &srvHeap.heap);
}

void DXSRVHeap::SetRootParameter()
{
	DXRootParameterManager* rpM = DXRootParameterManager::GetInstance();
	rpIndex = rpM->PushBackDescriptorTable(descriptorRange);
}

void DXSRVHeap::SetCommand(const UINT index) 
{
	// SRV�q�[�v�̐擪�n���h�����擾 (SRV���w�肵�Ă���͂�)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = 
		srvHeap.heap->GetGPUDescriptorHandleForHeapStart();

	if (index > 0)
	{
		for (size_t i = 0; i < index; i++)
		{
			srvGpuHandle.ptr += incrementSize;
		}
	}

	cmdList->List()->SetGraphicsRootDescriptorTable(rpIndex, srvGpuHandle);
}

DXSRVHeap* DXSRVHeap::GetInstance()
{
	static DXSRVHeap instance;
	return &instance;
}