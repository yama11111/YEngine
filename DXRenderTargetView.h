#pragma once
#include "DXDescriptorHeap.h"
#include <dxgi1_6.h>
#include <vector>

#pragma comment(lib, "dxgi.lib")

class DXRenderTargetView
{
private:
	DXDescriptorHeap rtv;
	// バックバッファ
	std::vector<ID3D12Resource*> backBuffers;
public:
	void Create(IDXGISwapChain4* swapChain, DXGI_SWAP_CHAIN_DESC1 swapChainDesc);
	DXDescriptorHeap RenderTargetView();
	std::vector<ID3D12Resource*> BackBaffers();
	ID3D12Resource* BackBaffer(const int index);
};

