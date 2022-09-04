#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	namespace Utility
	{
		class DescriptorHeap
		{
		public:
			// デスクリプタヒープ設定
			D3D12_DESCRIPTOR_HEAP_DESC desc{};
		private:
			Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap = nullptr;
		public:
			void Create();
			ID3D12DescriptorHeap* Get();
		};
	}
}
