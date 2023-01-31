#include "DescriptorHeap.h"
#include "YAssert.h"

using YDX::DescriptorHeap;

ID3D12Device* DescriptorHeap::pDevice_ = nullptr;
ID3D12GraphicsCommandList* DescriptorHeap::pCommandList_ = nullptr;

void DescriptorHeap::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.pDevice_);
	assert(state.pCommandList_);

	pDevice_  = state.pDevice_;
	pCommandList_ = state.pCommandList_;
}

void DescriptorHeap::Initialize()
{
	srvCount_ = uavCount_ = cbvCount_ = 0;

	// �f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // �V�F�[�_�[���猩����悤��
	heapDesc.NumDescriptors = MaxSRVCount_  + MaxUAVCount_ + MaxCBVCount_;

	// �ݒ�����ƂɃf�X�N���v�^�q�[�v(SRV,UAV,CBV�p)�𐶐�
	Result(pDevice_->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&descriptorHeap_)));
}

void DescriptorHeap::CreateSRV(ID3D12Resource* buff, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc, 
	D3D12_CPU_DESCRIPTOR_HANDLE& cpuHandle, D3D12_GPU_DESCRIPTOR_HANDLE& gpuHandle)
{
	assert(srvCount_ < MaxSRVCount_);

	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(CPU)���擾
	cpuHandle = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(GPU)���擾
	gpuHandle = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// �C���N�������g�T�C�Y�l��
	UINT incSize = pDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// SRV�����镪�����n���h����i�߂�
	cpuHandle.ptr += static_cast<SIZE_T>(incSize * srvCount_);
	gpuHandle.ptr += static_cast<SIZE_T>(incSize * srvCount_);

	// �n���h���̎w���ʒu��SRV�쐬
	pDevice_->CreateShaderResourceView(buff, &srvDesc, cpuHandle);

	srvCount_++;
}

void DescriptorHeap::CreateUAV(ID3D12Resource* buff, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc)
{
	assert(uavCount_ < MaxUAVCount_);

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;

	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(CPU)���擾
	cpuHandle = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(GPU)���擾
	gpuHandle = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// �C���N�������g�T�C�Y�l��
	UINT incSize = pDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// UAV + �ő�SRV�����镪�����n���h����i�߂�
	cpuHandle.ptr += static_cast<SIZE_T>(incSize * (uavCount_ + MaxSRVCount_));
	gpuHandle.ptr += static_cast<SIZE_T>(incSize * (uavCount_ + MaxSRVCount_));

	// �n���h���̎w���ʒu��UAV�쐬
	pDevice_->CreateUnorderedAccessView(buff, nullptr, &uavDesc, cpuHandle);

	uavCount_++;
}

void DescriptorHeap::CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc)
{
	assert(cbvCount_ < MaxCBVCount_);

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;

	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(CPU)���擾
	cpuHandle = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();

	// �C���N�������g�T�C�Y�l��
	UINT incSize = pDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// CBV + �ő�SRV + �ő�UAV �����镪�����n���h����i�߂�
	cpuHandle.ptr += static_cast<SIZE_T>(incSize * (cbvCount_ + MaxSRVCount_ + MaxUAVCount_));

	// �n���h���̎w���ʒu��CBV�쐬
	pDevice_->CreateConstantBufferView(&cbvDesc, cpuHandle);

	cbvCount_++;
}

void DescriptorHeap::SetDrawCommand()
{
	// SRV�q�[�v�̐ݒ�R�}���h
	ID3D12DescriptorHeap* ppHeaps[] = { descriptorHeap_.Get() };
	pCommandList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}
