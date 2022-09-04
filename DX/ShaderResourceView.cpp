#include "ShaderResourceView.h"
#include "Device.h"
#include "RootParameterManager.h"
#include <assert.h>

using DX::ShaderResourceView;

ID3D12GraphicsCommandList* ShaderResourceView::pCmdList = nullptr;

ShaderResourceView* ShaderResourceView::GetInstance()
{
	static ShaderResourceView instance;
	return &instance;
}

void ShaderResourceView::StaticInit(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList != nullptr);
	pCmdList = pCommandList;
}

ShaderResourceView::ShaderResourceView()
{
	// SRV�̍ő��
	const size_t kMaxSRVCount = 2056;

	// �f�X�N���v�^�q�[�v�̐ݒ�
	srv.desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srv.desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // �V�F�[�_�[���猩����悤��
	srv.desc.NumDescriptors = kMaxSRVCount;

	// �ݒ�����Ƃ�SRV�p�f�X�N���v�^�q�[�v�𐶐�
	srv.Create();

	// SRV�q�[�v�̐擪�n���h�����擾
	handle = srv.Get()->GetCPUDescriptorHandleForHeapStart();

	Device* dev = Device::GetInstance();
	incrementSize = dev->Get()->
		GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// �f�X�N���v�^�����W�̐ݒ�
	descriptorRange.NumDescriptors = 1; // 1�x�̕`��Ɏg���e�N�X�`����1���Ȃ̂�1
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0; // �e�N�X�`�����W�X�^0��
	descriptorRange.OffsetInDescriptorsFromTableStart =
		D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
}

UINT ShaderResourceView::SetSRV(ID3D12Resource* texBuff, D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc)
{
	Device* dev = Device::GetInstance();

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	dev->Get()->CreateShaderResourceView(texBuff, &srvDesc, handle);

	// ��n���h����i�߂�
	handle.ptr += incrementSize;

	UINT result = index;
	index++;

	return result;
}

void ShaderResourceView::SetDescriptorHeaps()
{
	// SRV�q�[�v�̐ݒ�R�}���h
	ID3D12DescriptorHeap* ppHeaps[] = { srv.Get() };
	pCmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}

void ShaderResourceView::SetRootParameter()
{
	RootParameterManager* rpM = RootParameterManager::GetInstance();
	rpIndex = rpM->PushBackDescriptorTable(descriptorRange);
}

void ShaderResourceView::SetCommand(const UINT index)
{
	// SRV�q�[�v�̐擪�n���h�����擾 (SRV���w�肵�Ă���͂�)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = 
		srv.Get()->GetGPUDescriptorHandleForHeapStart();

	if (index > 0)
	{
		for (size_t i = 0; i < index; i++)
		{
			srvGpuHandle.ptr += incrementSize;
		}
	}

	pCmdList->SetGraphicsRootDescriptorTable(rpIndex, srvGpuHandle);
}