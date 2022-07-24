#include "DXSwapChain.h"
#include "Result.h"
#include "Def.h"

void DXSwapChain::Init()
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
