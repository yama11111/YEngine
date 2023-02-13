#pragma once
#include <d3d12.h>
#include "Vector2.h"

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	class ScreenDesc
	{
	private:
		// �r���[�|�[�g�ݒ�R�}���h
		D3D12_VIEWPORT viewport_{};
		// �V�U�[��`
		D3D12_RECT scissorRect_{};
	public:
		// ������ (���� : ����, �E��)
		void Initialize(const YMath::Vector2& topLeft, const YMath::Vector2& bottomRight);
		// �`��O�R�}���h
		void SetDrawCommand();
	private:
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCommandList_;
	public:
		// �ÓI�����o������
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
	};
}
