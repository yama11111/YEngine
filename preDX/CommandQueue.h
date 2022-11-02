#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class CommandQueue
	{
	private:
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue = nullptr;
	public:
		void Create();
		ID3D12CommandQueue* Get();
	};
}