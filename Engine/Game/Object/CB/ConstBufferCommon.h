#pragma once
#include "DescriptorHeap.h"

namespace YDX
{
	// �萔�o�b�t�@�R�����N���X
	class ConstBufferCommon
	{

	protected:

		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* spCmdList_;

		// �ÓI�f�X�N���v�^�[�q�[�v�|�C���^
		static DescriptorHeap* spDescHeap_;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pDevice"> : �f�o�C�X�|�C���^</param>
		/// <param name="pDescHeap"> : �f�X�N���v�^�[�q�[�v�|�C���^</param>
		static void StaticInitialize(ID3D12GraphicsCommandList* pCmdList, DescriptorHeap* pDescHeap);

	};
}
