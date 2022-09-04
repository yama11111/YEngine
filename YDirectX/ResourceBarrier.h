#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class ResourceBarrier
	{
	private:
		D3D12_RESOURCE_BARRIER barrierDesc{};
		ID3D12GraphicsCommandList* pCmdList = nullptr;
	public:
		void Initialize(ID3D12GraphicsCommandList* pCommandList);
		void SetCurrentBackBuffer(ID3D12Resource* backBuffer);
		enum State
		{
			RenderTarget = 0, // •`‰æ
			Present = 1, // •\Ž¦
		};
		// •`‰æ : 0, •\Ž¦ : 1
		bool ChangeState(const int state);
	};
}
