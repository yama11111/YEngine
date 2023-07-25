#pragma once
#include "BaseConstBuffer.h"

namespace YGame
{
	// �萔�o�b�t�@
	template <typename CBData>
	class ConstBuffer final : 
		public YDX::BaseConstBuffer
	{

	public:

		// �萔�o�b�t�@�f�[�^
		CBData data_{};
	
	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <returns>���I�C���X�^���X</returns>
		static ConstBuffer* Create(const bool isMutable = true);

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="data">�萔�o�b�t�@�f�[�^</param>
		/// <returns>���I�C���X�^���X</returns>
		static ConstBuffer* Create(const CBData& data, const bool isMutable = true);

	public:

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="rootParamIndex"> : ���[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(const uint32_t rootParamIndex) override;

	public:

		virtual ~ConstBuffer() = default;
	
	private:

		// �}�b�s���O�p
		CBData* map_ = nullptr;

	private:

		/// <summary>
		/// �萔�o�b�t�@�̃T�C�Y�擾
		/// </summary>
		/// <returns>�萔�o�b�t�@�̃T�C�Y</returns>
		size_t SizeOfCBData() override;

		/// <summary>
		/// �}�b�s���O�p�f�[�^�_�u���|�C���^�擾
		/// </summary>
		/// <returns>�}�b�s���O�p�f�[�^�_�u���|�C���^</returns>
		void** MapDataPtrPtr() override;

	private:

		ConstBuffer() = default;

	};

	template<typename CBData>
	inline ConstBuffer<CBData>* ConstBuffer<CBData>::Create(const bool isMutable)
	{
		ConstBuffer* newConstBuffer = new ConstBuffer();

		newConstBuffer->CreateBuffer(isMutable);

		*newConstBuffer->map_ = newConstBuffer->data_ = {};

		return newConstBuffer;
	}

	template<typename CBData>
	ConstBuffer<CBData>* ConstBuffer<CBData>::Create(const CBData& data, const bool isMutable)
	{
		ConstBuffer* newConstBuffer = new ConstBuffer();

		newConstBuffer->CreateBuffer(isMutable);

		*newConstBuffer->*map_ = newConstBuffer->data_ = data;

		return newConstBuffer;
	}

	template<typename CBData>
	void ConstBuffer<CBData>::SetDrawCommand(const uint32_t rootParamIndex) 
	{
		// �l���X�V
		*map_ = data_;

		// �萔�o�b�t�@�r���[�ݒ�R�}���h
		spCmdList_->SetGraphicsRootConstantBufferView(static_cast<UINT>(rootParamIndex), viewDesc_.BufferLocation);
	}

	template<typename CBData>
	size_t ConstBuffer<CBData>::SizeOfCBData()
	{
		return sizeof(CBData);
	}

	template<typename CBData>
	void** ConstBuffer<CBData>::MapDataPtrPtr()
	{
		return (void**)&map_;
	}
}
