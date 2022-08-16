#include "DXSRVHeap.h"
#include "DXDevice.h"
#include "DXRootParameterManager.h"

DXSRVHeap::DXSRVHeap()
{
	// SRVの最大個数
	const size_t kMaxSRVCount = 2056;

	// デスクリプタヒープの設定
	srvHeap.hDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeap.hDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // シェーダーから見えるように
	srvHeap.hDesc.NumDescriptors = kMaxSRVCount;

	// 設定をもとにSRV用デスクリプタヒープを生成
	srvHeap.Create();

	// SRVヒープの先頭ハンドルを取得
	srvHandle = srvHeap.heap->GetCPUDescriptorHandleForHeapStart();

	DXDevice* dev = DXDevice::GetInstance();
	incrementSize = dev->Device()->
		GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	cmdList = DXCommandList::GetInstance();

	// デスクリプタレンジの設定
	descriptorRange.NumDescriptors = 1; // 1度の描画に使うテクスチャが1枚なので1
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0; // テクスチャレジスタ0番
	descriptorRange.OffsetInDescriptorsFromTableStart =
		D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
}

UINT DXSRVHeap::SetSRV(ID3D12Resource* texBuff, D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc)
{
	DXDevice* dev = DXDevice::GetInstance();

	// ハンドルの指す位置にシェーダーリソースビュー作成
	dev->Device()->CreateShaderResourceView(texBuff, &srvDesc, srvHandle);

	// 一つハンドルを進める
	srvHandle.ptr += incrementSize;

	UINT result = index;
	index++;

	return result;
}

void DXSRVHeap::SetDescriptorHeaps()
{
	// SRVヒープの設定コマンド
	cmdList->List()->SetDescriptorHeaps(1, &srvHeap.heap);
}

void DXSRVHeap::SetRootParameter()
{
	DXRootParameterManager* rpM = DXRootParameterManager::GetInstance();
	rpIndex = rpM->PushBackDescriptorTable(descriptorRange);
}

void DXSRVHeap::SetCommand(const UINT index) 
{
	// SRVヒープの先頭ハンドルを取得 (SRVを指定しているはず)
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