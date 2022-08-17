#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

struct DXResourceInfo
{
	D3D12_HEAP_PROPERTIES heapProp = {}; // バッファ設定
	D3D12_RESOURCE_DESC resDesc{}; // リソース設定
};

// 深度用
struct DXResourceInfo2 : public DXResourceInfo
{
	D3D12_CLEAR_VALUE clearValue{}; // 深度値のクリア設定
};