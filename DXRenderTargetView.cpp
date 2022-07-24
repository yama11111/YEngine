#include "DXRenderTargetView.h"
#include "DXDevice.h"
#include "Result.h"

void DXRenderTargetView::Create(IDXGISwapChain4* swapChain, DXGI_SWAP_CHAIN_DESC1 swapChainDesc)
{
	DXDevice* dev = DXDevice::GetInstance();
	rtv.hDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;		// レンダーターゲットビュー
	rtv.hDesc.NumDescriptors = swapChainDesc.BufferCount; // 裏表の2つ
	// デスクリプタヒープ生成
	rtv.Create();
	backBuffers.resize(swapChainDesc.BufferCount);

	// スワップチェーンの全てのバッファについて処理する
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		// スワップチェーンからバッファ取得
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		// デスクリプタヒープのハンドル取得
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtv.heap->GetCPUDescriptorHandleForHeapStart();
		// 裏か表かでアドレスがずれる
		rtvHandle.ptr += i * dev->Device()->GetDescriptorHandleIncrementSize(rtv.hDesc.Type);
		// レンダーターゲットビュー設定
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		// シェーダーの計算結果をSRGBに変換して書き込む
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		// レンダーターゲットビュー生成
		dev->Device()->CreateRenderTargetView(backBuffers[i], &rtvDesc, rtvHandle);
	}
}

DXDescriptorHeap DXRenderTargetView::RenderTargetView()
{
	return rtv;
}

std::vector<ID3D12Resource*> DXRenderTargetView::BackBaffers()
{
	return backBuffers;
}

ID3D12Resource* DXRenderTargetView::BackBaffer(const int index)
{
	if (backBuffers.size() <= index) return backBuffers[0];
	return backBuffers[index];
}
