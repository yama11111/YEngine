#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

struct DXResourceInfo
{
	D3D12_HEAP_PROPERTIES heapProp = {}; // �o�b�t�@�ݒ�
	D3D12_RESOURCE_DESC resDesc{}; // ���\�[�X�ݒ�
};
