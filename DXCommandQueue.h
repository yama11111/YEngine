#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

class DXCommandQueue
{
private:
	ID3D12CommandQueue* commandQueue = nullptr;
	//�R�}���h�L���[�ݒ�
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
public:
	void Create();
	ID3D12CommandQueue* Queue();
};
