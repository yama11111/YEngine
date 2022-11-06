#pragma once
#include <d3d12.h>
#include "Vec2.h"

#pragma comment(lib, "d3d12.lib")

namespace DX
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
		void Initialize(const Math::Vec2& topLeft, const Math::Vec2& bottomRight);
		// �`��O�R�}���h
		void SetDrawCommand();
	private:
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCmdList_;
	public:
		// �ÓI�����o������
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
	};
}
