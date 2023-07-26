#pragma once
#include "DescriptorHeap.h"
#include "GPUResource.h"
#include <cstdint>
#include <string>

namespace YDX
{
	class ConstBufferCommon
	{
	
	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pDevice"> : �f�o�C�X�|�C���^</param>
		/// <param name="pDescHeap"> : �f�X�N���v�^�[�q�[�v�|�C���^</param>
		static void StaticInitialize(ID3D12GraphicsCommandList* pCmdList, YDX::DescriptorHeap* pDescHeap);

	protected:

		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* spCmdList_;

		// �ÓI�f�X�N���v�^�[�q�[�v�|�C���^
		static YDX::DescriptorHeap* spDescHeap_;
	};

	class BaseConstBuffer : 
		protected ConstBufferCommon
	{

	public:

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="rootParamIndex"> : ���[�g�p�����[�^�ԍ�</param>
		virtual void SetDrawCommand(const uint32_t rootParamIndex);

		/// <summary>
		/// �萔�o�b�t�@�^�C�v���擾
		/// </summary>
		/// <returns>�萔�o�b�t�@�^�C�v��</returns>
		virtual std::string TypeName() = 0;

	public:

		BaseConstBuffer() = default;
	
		virtual ~BaseConstBuffer() = default;
	
	protected:

		// �o�b�t�@
		YDX::GPUResource buff_;

		// CBV�ݒ�
		D3D12_CONSTANT_BUFFER_VIEW_DESC viewDesc_{};
	
	protected:

		/// <summary>
		/// �萔�o�b�t�@�̐��� + �}�b�s���O
		/// </summary>
		/// <param name="isMutable">�V�[���J�ڎ��N���A���邩</param>
		void CreateBuffer(const bool isMutable);

		/// <summary>
		/// �萔�o�b�t�@�̃T�C�Y�擾
		/// </summary>
		/// <returns>�萔�o�b�t�@�̃T�C�Y</returns>
		virtual size_t SizeOfCBData() = 0;

		/// <summary>
		/// �}�b�s���O�p�f�[�^�_�u���|�C���^�擾
		/// </summary>
		/// <returns>�}�b�s���O�p�f�[�^�_�u���|�C���^</returns>
		virtual void** MapDataPtrPtr() = 0;

	};
}
