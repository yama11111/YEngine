#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

class DXResourceBarrier
{
private:
	D3D12_RESOURCE_BARRIER barrierDesc{};
public:
	void SetCurrentBackBuffer(ID3D12Resource* backBuffer);
	enum State
	{
		RenderTarget = 0, // 描画
		Present = 1, // 表示
	};
	// 描画 : 0, 表示 : 1
	bool ChangeState(const int state);
};

