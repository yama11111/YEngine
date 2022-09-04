#pragma once
#include "Utility/DescriptorHeap.h"
#include <dxgi1_6.h>
#include <vector>

#pragma comment(lib, "dxgi.lib")

namespace DX
{
	class RenderTargetView
	{
	private:
		Utility::DescriptorHeap rtv;
		// バックバッファ
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	public:
		void Create(IDXGISwapChain4* swapChain, const DXGI_SWAP_CHAIN_DESC1& swapChainDesc);
		Utility::DescriptorHeap Get();
		std::vector<ID3D12Resource*> BackBaffers();
		ID3D12Resource* BackBaffer(const int index);
	};
}
