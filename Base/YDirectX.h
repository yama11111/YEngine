#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <vector>
#include "Vec2.h"
#include "Vec4.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace DX 
{
	class YDirectX
	{
	private:
		Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_ = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Device> device_ = nullptr;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator_ = nullptr;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList_ = nullptr;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue_ = nullptr;
		Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_ = nullptr;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtv_ = nullptr;
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers_;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsv_ = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Resource> dsvBuff_ = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Fence> fence_ = nullptr;
		UINT64 fenceValue_ = 0;
	public:
		bool Initialize(const HWND& hwnd, const Math::Vec2& size = { 1280, 720 });
		void PreDraw(const Math::Vec4& clearColor);
		void PostDraw();
		ID3D12Device* Device() { return device_.Get(); }
		ID3D12GraphicsCommandList* CommandList() { return cmdList_.Get(); }
	};
}