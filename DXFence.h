#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

class DXFence
{
private:
	ID3D12Fence* fence = nullptr;
	UINT64 fenceVal = 0;
public:
	void Create();
	bool ConfirmCommandComplate(ID3D12CommandQueue* commandQueue);
};

