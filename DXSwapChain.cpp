#include "DXSwapChain.h"
#include "Result.h"
#include "Def.h"

void DXSwapChain::Init()
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

void DXSwapChain::Create(IDXGIFactory7* dxgiFactory, ID3D12CommandQueue* commandQueue, const HWND& hwnd)
{
	Result::Check(dxgiFactory->CreateSwapChainForHwnd(
		commandQueue, hwnd, &swapChainDesc, nullptr, nullptr,
		(IDXGISwapChain1**)&swapChain));
}

IDXGISwapChain4* DXSwapChain::SwapChain()
{
	return swapChain;
}

DXGI_SWAP_CHAIN_DESC1 DXSwapChain::Desc()
{
	return swapChainDesc;
}
