#pragma once
#include "Device.h"
#include "CommandList.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Fence.h"
#include "ResourceBarrier.h"
#include "DebugLayer.h"

namespace DX 
{
	class YDirectX
	{
	private:
		Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
		Device* dev = nullptr;
		CommandList cmdList;
		CommandQueue cmdQue;
		SwapChain swpChain;
		RenderTargetView rtv;
		DepthStencilView dsv;
		Fence fence;
		ResourceBarrier rscBarrier;
		DebugLayer debugLayer;
	public:
		bool Initialize(const HWND& hwnd);
		void PreDraw();
		void PostDraw();
		ID3D12GraphicsCommandList* GetCommandList();
	public:
		static YDirectX* GetInstance();
	private:
		YDirectX() = default;
		~YDirectX() = default;
		YDirectX(const YDirectX&) = delete;
		const YDirectX& operator=(const YDirectX&) = delete;
	};
}