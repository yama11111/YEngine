#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace DX
{
	class SwapChain
	{
	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain = nullptr;
		// スワップチェーン設定
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	public:
		void Initialize();
		void Create(IDXGIFactory7* dxgiFactory, ID3D12CommandQueue* commandQueue, const HWND& hwnd);
		IDXGISwapChain4* Get();
		DXGI_SWAP_CHAIN_DESC1 Desc();
	};
}
