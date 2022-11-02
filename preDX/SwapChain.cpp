#include "SwapChain.h"
#include "Utility/Result.h"
#include "Def.h"

using DX::SwapChain;

void SwapChain::Initialize()
{
	swapChainDesc.Width = (UINT)WIN_SIZE.x;
	swapChainDesc.Height = (UINT)WIN_SIZE.y;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		  // 色情報の書式
	swapChainDesc.SampleDesc.Count = 1;						  // マルチサンプルしない
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;		  // バックバッファ用
	swapChainDesc.BufferCount = 2;							  // バッファ数を2つに設定
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // フリップ後は破棄
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
}

void SwapChain::Create(IDXGIFactory7* dxgiFactory, ID3D12CommandQueue* commandQueue, const HWND& hwnd)
{
	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain1;

	Utility::Result::Check(dxgiFactory->CreateSwapChainForHwnd(
		commandQueue, 
		hwnd, 
		&swapChainDesc, 
		nullptr, 
		nullptr,
		&swapChain1));

	swapChain1.As(&swapChain);
}

IDXGISwapChain4* SwapChain::Get()
{
	return swapChain.Get();
}

DXGI_SWAP_CHAIN_DESC1 SwapChain::Desc()
{
	return swapChainDesc;
}
