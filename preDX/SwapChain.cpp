#include "SwapChain.h"
#include "Utility/Result.h"
#include "Def.h"

using DX::SwapChain;

void SwapChain::Initialize()
{
	swapChainDesc.Width = (UINT)WIN_SIZE.x;
	swapChainDesc.Height = (UINT)WIN_SIZE.y;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		  // �F���̏���
	swapChainDesc.SampleDesc.Count = 1;						  // �}���`�T���v�����Ȃ�
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;		  // �o�b�N�o�b�t�@�p
	swapChainDesc.BufferCount = 2;							  // �o�b�t�@����2�ɐݒ�
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // �t���b�v��͔j��
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
