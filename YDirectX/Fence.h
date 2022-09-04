#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace DX 
{
	class Fence
	{
	private:
		Microsoft::WRL::ComPtr<ID3D12Fence> fence = nullptr;
		UINT64 fenceVal = 0;
	public:
		void Create();
		bool ConfirmCommandComplate(ID3D12CommandQueue* commandQueue);
	};
}
