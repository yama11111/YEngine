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
	// SRVの最大個数
	const size_t kMaxSRVCount = 2056;

	// デスクリプタヒープの設定
	srv.desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srv.desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // シェーダーから見えるように
	srv.desc.NumDescriptors = kMaxSRVCount;

	// 設定をもとにSRV用デスクリプタヒープを生成
	srv.Create();

	// SRVヒープの先頭ハンドルを取得
	handle = srv.Get()->GetCPUDescriptorHandleForHeapStart();

	Device* dev = Device::GetInstance();
	incrementSize = dev->Get()->
		GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// デスクリプタレンジの設定
	descriptorRange.NumDescriptors = 1; // 1度の描画に使うテクスチャが1枚なので1
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0; // テクスチャレジスタ0番
	descriptorRange.OffsetInDescriptorsFromTableStart =
		D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
}

UINT ShaderResourceView::SetSRV(ID3D12Resource* texBuff, D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc)
{
	Device* dev = Device::GetInstance();

	// ハンドルの指す位置にシェーダーリソースビュー作成
	dev->Get()->CreateShaderResourceView(texBuff, &srvDesc, handle);

	// 一つハンドルを進める
	handle.ptr += incrementSize;

	UINT result = index;
	index++;

	return result;
}

void ShaderResourceView::SetDescriptorHeaps()
{
	// SRVヒープの設定コマンド
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
	// SRVヒープの先頭ハンドルを取得 (SRVを指定しているはず)
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