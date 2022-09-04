#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	namespace Utility
	{
		struct ResourceInfo
		{
			D3D12_HEAP_PROPERTIES heapProp = {}; // �o�b�t�@�ݒ�
			D3D12_RESOURCE_DESC resDesc{}; // ���\�[�X�ݒ�
		};

		// �[�x�p
		struct ResourceInfo2 : public ResourceInfo
		{
			D3D12_CLEAR_VALUE clearValue{}; // �[�x�l�̃N���A�ݒ�
		};
	}
}