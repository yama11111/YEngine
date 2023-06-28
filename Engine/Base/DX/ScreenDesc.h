#pragma once
#include <d3d12.h>
#include "Vector2.h"
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	class ScreenDesc
	{
	private:
		
		// �r���[�|�[�g�ݒ�R�}���h
		std::vector<D3D12_VIEWPORT> viewport_;
		
		// �V�U�[��`
		std::vector<D3D12_RECT> scissorRect_;
	
	public:
		
		// ������ (���� : ����, �E��)
		void Initialize(const YMath::Vector2& topLeft, const YMath::Vector2& bottomRight, const size_t descNum = 1);
		
		// �`��O�R�}���h
		void SetDrawCommand();
	
	private:
		
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* spCmdList_;
	
	public:
		
		// �ÓI�����o������
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
	};
}
