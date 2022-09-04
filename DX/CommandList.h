#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class CommandList
	{
	private:
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator = nullptr;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> list = nullptr;
	public:
		void Create();
		void Reset();
		ID3D12GraphicsCommandList* Get();
		ID3D12CommandAllocator* GetAllocator();
	};
}