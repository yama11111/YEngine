#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

class DXDescriptorHeap
{
public:
	ID3D12DescriptorHeap* heap = nullptr;
	// �f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC hDesc{};
public:
	void Create();
};

