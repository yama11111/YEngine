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
		RenderTarget = 0, // �`��
		Present = 1, // �\��
	};
	// �`�� : 0, �\�� : 1
	bool ChangeState(const int state);
};

