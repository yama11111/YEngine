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

	// デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // シェーダーから見えるように
	heapDesc.NumDescriptors = MaxSRVCount_  + MaxUAVCount_ + MaxCBVCount_;

	// 設定をもとにデスクリプタヒープ(SRV,UAV,CBV用)を生成
	Result(pDevice_->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&descriptorHeap_)));
}

void DescriptorHeap::CreateSRV(ID3D12Resource* buff, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc, 
	D3D12_CPU_DESCRIPTOR_HANDLE& cpuHandle, D3D12_GPU_DESCRIPTOR_HANDLE& gpuHandle)
{
	assert(srvCount_ < MaxSRVCount_);

	// デスクリプターヒープの先頭ハンドル(CPU)を取得
	cpuHandle = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// デスクリプターヒープの先頭ハンドル(GPU)を取得
	gpuHandle = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// インクリメントサイズ獲得
	UINT incSize = pDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// SRVがある分だけハンドルを進める
	cpuHandle.ptr += static_cast<SIZE_T>(incSize * srvCount_);
	gpuHandle.ptr += static_cast<SIZE_T>(incSize * srvCount_);

	// ハンドルの指す位置にSRV作成
	pDevice_->CreateShaderResourceView(buff, &srvDesc, cpuHandle);

	srvCount_++;
}

void DescriptorHeap::CreateUAV(ID3D12Resource* buff, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc)
{
	assert(uavCount_ < MaxUAVCount_);

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;

	// デスクリプターヒープの先頭ハンドル(CPU)を取得
	cpuHandle = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// デスクリプターヒープの先頭ハンドル(GPU)を取得
	gpuHandle = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// インクリメントサイズ獲得
	UINT incSize = pDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// UAV + 最大SRVがある分だけハンドルを進める
	cpuHandle.ptr += static_cast<SIZE_T>(incSize * (uavCount_ + MaxSRVCount_));
	gpuHandle.ptr += static_cast<SIZE_T>(incSize * (uavCount_ + MaxSRVCount_));

	// ハンドルの指す位置にUAV作成
	pDevice_->CreateUnorderedAccessView(buff, nullptr, &uavDesc, cpuHandle);

	uavCount_++;
}

void DescriptorHeap::CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc)
{
	assert(cbvCount_ < MaxCBVCount_);

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;

	// デスクリプターヒープの先頭ハンドル(CPU)を取得
	cpuHandle = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();

	// インクリメントサイズ獲得
	UINT incSize = pDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// CBV + 最大SRV + 最大UAV がある分だけハンドルを進める
	cpuHandle.ptr += static_cast<SIZE_T>(incSize * (cbvCount_ + MaxSRVCount_ + MaxUAVCount_));

	// ハンドルの指す位置にCBV作成
	pDevice_->CreateConstantBufferView(&cbvDesc, cpuHandle);

	cbvCount_++;
}

void DescriptorHeap::SetDrawCommand()
{
	// SRVヒープの設定コマンド
	ID3D12DescriptorHeap* ppHeaps[] = { descriptorHeap_.Get() };
	pCommandList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}
