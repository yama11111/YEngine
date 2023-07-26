#pragma once
#include "BaseConstBuffer.h"

namespace YGame
{
	// �萔�o�b�t�@
	template <typename CBType>
	class ConstBuffer final : 
		public YDX::BaseConstBuffer
	{

	public:

		// �萔�o�b�t�@�f�[�^
		CBType::Data data_{};
	
	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <returns>���I�C���X�^���X</returns>
		static ConstBuffer* Create(const bool isMutable = true);

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="type">�萔�o�b�t�@�^�C�v</param>
		/// <returns>���I�C���X�^���X</returns>
		static ConstBuffer* Create(const CBType& type, const bool isMutable = true);

	public:

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="rootParamIndex"> : ���[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(const uint32_t rootParamIndex) override;

		/// <summary>
		/// �萔�o�b�t�@�^�C�v���擾
		/// </summary>
		/// <returns>�萔�o�b�t�@�^�C�v��</returns>
		std::string TypeName() override;

	public:

		virtual ~ConstBuffer() = default;
	
	private:

		// �}�b�s���O�p
		CBType::Data* map_ = nullptr;

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

	template<typename CBType>
	inline ConstBuffer<CBType>* ConstBuffer<CBType>::Create(const bool isMutable)
	{
		ConstBuffer* newConstBuffer = new ConstBuffer();

		newConstBuffer->CreateBuffer(isMutable);

		*newConstBuffer->map_ = newConstBuffer->data_ = {};

		return newConstBuffer;
	}

	template<typename CBType>
	ConstBuffer<CBType>* ConstBuffer<CBType>::Create(const CBType& data, const bool isMutable)
	{
		ConstBuffer* newConstBuffer = new ConstBuffer();

		newConstBuffer->CreateBuffer(isMutable);

		*newConstBuffer->*map_ = newConstBuffer->data_ = data;

		return newConstBuffer;
	}

	template<typename CBType>
	void ConstBuffer<CBType>::SetDrawCommand(const uint32_t rootParamIndex) 
	{
		// �l���X�V
		*map_ = data_;

		BaseConstBuffer::SetDrawCommand(rootParamIndex);
	}

	template<typename CBType>
	inline std::string ConstBuffer<CBType>::TypeName()
	{
		return CBType::TypeName();
	}

	template<typename CBType>
	size_t ConstBuffer<CBType>::SizeOfCBData()
	{
		return sizeof(CBType::Data);
	}

	template<typename CBType>
	void** ConstBuffer<CBType>::MapDataPtrPtr()
	{
		return (void**)&map_;
	}
}
