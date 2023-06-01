#pragma once
#include "GPUResource.h"
#include "DescriptorHeap.h"

namespace YDX
{
	// �萔�o�b�t�@�R�����N���X
	class ConstBufferCommon
	{
	protected:

		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* spCmdList_;

		// �ÓI�f�X�N���v�^�[�q�[�v�N���X
		static DescriptorHeap* spDescHeap_;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pDevice"> : �f�o�C�X�|�C���^</param>
		/// <param name="pDescHeap"> : �f�X�N���v�^�[�q�[�v�|�C���^</param>
		static void StaticInitialize(ID3D12GraphicsCommandList* pCmdList, DescriptorHeap* pDescHeap);

	};


	// �萔�o�b�t�@
	template <typename T>
	class ConstBuffer : private ConstBufferCommon
	{
	public:

		// �}�b�s���O�p
		T* map_ = nullptr;

	private:

		// �o�b�t�@
		GPUResource buff_;

		// CBV�ݒ�
		D3D12_CONSTANT_BUFFER_VIEW_DESC viewDesc_{};

	public:

		/// <summary>
		/// �萔�o�b�t�@�̐��� + �}�b�s���O
		/// </summary>
		/// <param name="isMutable"> : ���Z�b�g���邩</param>
		void Create(const bool isMutable);

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="rootParamIndex"> : ���[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(const UINT rootParamIndex);

	};
}