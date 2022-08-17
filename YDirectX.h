#pragma once
#include "DXDevice.h"
#include "DXCommandList.h"
#include "DXCommandQueue.h"
#include "DXSwapChain.h"
#include "DXRenderTargetView.h"
#include "DXDSVHeap.h"
#include "DXFence.h"
#include "DXResourceBarrier.h"
#include "DXDebugLayer.h"

class YDirectX
{
private:
	IDXGIFactory7* dxgiFactory = nullptr;
	DXDevice* dev = nullptr;
	DXCommandList* cmdList = nullptr;
	DXCommandQueue cmdQue;
	DXSwapChain swpChain;
	DXRenderTargetView rtv;
	DXDSVHeap dsvHeap;
	DXFence fence;
	DXResourceBarrier rscBarrier;
	DXDebugLayer debugLayer;
public:
	int Init(const HWND& hwnd);
	int PreDraw();
	int PostDraw();
public:
	static YDirectX* GetInstance();
private:
	YDirectX() = default;
	~YDirectX() = default;
	YDirectX(const YDirectX&) = delete;
	const YDirectX& operator=(const YDirectX&) = delete;
};