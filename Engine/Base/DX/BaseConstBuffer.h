#pragma once
#include "DescriptorHeap.h"
#include "GPUResource.h"
#include <cstdint>
#include <string>

namespace YGame
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

	// ���萔�o�b�t�@�N���X
	class BaseConstBuffer : 
		protected ConstBufferCommon
	{

	public:

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="rootParamIndex"> : ���[�g�p�����[�^�ԍ�</param>
		virtual void SetDrawCommand(const uint32_t rootParamIndex);
	
	public:

		/// <summary>
		/// �^�O�擾
		/// </summary>
		/// <returns>�^�O��</returns>
		virtual const std::string Tag() const = 0;

	public:

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
		/// <param name="dataSize"> : �f�[�^�T�C�Y</param>
		/// <param name="map"> : �}�b�v�_�u���|�C���^</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		void CreateBuffer(const size_t dataSize, void** map, const bool isClearWhenTransition = true);

	protected:

		// �錾�𐧌�
		BaseConstBuffer() = default;
	
	private:

		// ������֎~
		BaseConstBuffer(const BaseConstBuffer&) = delete;

		const BaseConstBuffer& operator=(const BaseConstBuffer&) = delete;
	};
}
