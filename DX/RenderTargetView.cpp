#include "RenderTargetView.h"
#include "Device.h"
#include "Utility/Result.h"

using DX::RenderTargetView;

void RenderTargetView::Create(IDXGISwapChain4* swapChain, const DXGI_SWAP_CHAIN_DESC1& swapChainDesc)
{
	Device* dev = Device::GetInstance();
	rtv.desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // レンダーターゲットビュー
	rtv.desc.NumDescriptors = swapChainDesc.BufferCount; // 裏表の2つ
	// デスクリプタヒープ生成
	rtv.Create();
	backBuffers.resize(swapChainDesc.BufferCount);

	// スワップチェーンの全てのバッファについて処理する
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		// スワップチェーンからバッファ取得
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		// デスクリプタヒープのハンドル取得
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtv.Get()->GetCPUDescriptorHandleForHeapStart();
		// 裏か表かでアドレスがずれる
		rtvHandle.ptr += i * dev->Get()->GetDescriptorHandleIncrementSize(rtv.desc.Type);
		// レンダーターゲットビュー設定
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		// シェーダーの計算結果をSRGBに変換して書き込む
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		// レンダーターゲットビュー生成
		dev->Get()->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
}

DX::Utility::DescriptorHeap RenderTargetView::Get()
{
	return rtv;
}

std::vector<ID3D12Resource*> RenderTargetView::BackBaffers()
{
	std::vector<ID3D12Resource*> result;
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		result.push_back(backBuffers[i].Get());
	}
	return result;
}

ID3D12Resource* RenderTargetView::BackBaffer(const int index)
{
	if (backBuffers.size() <= index) return backBuffers[0].Get();
	return backBuffers[index].Get();
}
