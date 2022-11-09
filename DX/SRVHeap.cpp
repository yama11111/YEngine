#include "SRVHeap.h"
#include "YAssert.h"

using DX::SRVHeap;

ID3D12Device* SRVHeap::pDevice_ = nullptr;
ID3D12GraphicsCommandList* SRVHeap::pCmdList_ = nullptr;

void SRVHeap::StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList)
{
	assert(pDevice);
	assert(pCommandList);

	pDevice_ = pDevice;
	pCmdList_ = pCommandList;
}

void SRVHeap::Create()
{
	// デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // シェーダーから見えるように
	heapDesc.NumDescriptors = MaxSRVCount_;

	// 設定をもとにSRV用デスクリプタヒープを生成
	Result(pDevice_->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&srvHeap_)));
}

void SRVHeap::SetDrawCommand()
{
	// SRVヒープの設定コマンド
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap_.Get() };
	pCmdList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}
