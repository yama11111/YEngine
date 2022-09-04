#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	namespace Utility
	{
		struct ResourceInfo
		{
			D3D12_HEAP_PROPERTIES heapProp = {}; // バッファ設定
			D3D12_RESOURCE_DESC resDesc{}; // リソース設定
		};

		// 深度用
		struct ResourceInfo2 : public ResourceInfo
		{
			D3D12_CLEAR_VALUE clearValue{}; // 深度値のクリア設定
		};
	}
}