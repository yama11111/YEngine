#pragma once
#include "BaseConstBuffer.h"

namespace YGame
{
	// �萔�o�b�t�@
	template <typename CBType>
	class ConstBufferObject final : 
		public BaseConstBuffer
	{

	public:

		// �萔�o�b�t�@�f�[�^
		CBType::Data data_{};
	
	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		static ConstBufferObject* Create(const bool isClearWhenTransition = true);

	public:

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="rootParamIndex"> : ���[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(const uint32_t rootParamIndex) override;

		/// <summary>
		/// �^�O�擾
		/// </summary>
		/// <returns>�^�O��</returns>
		const std::string Tag() const override;

	public:

		virtual ~ConstBufferObject() = default;
	
	private:

		// �}�b�s���O�p
		CBType::Data* map_ = nullptr;

	private:

		// �錾�A������֎~
		ConstBufferObject() = default;

		ConstBufferObject(const ConstBufferObject&) = delete;

		const ConstBufferObject& operator=(const ConstBufferObject&) = delete;

	};

	template<typename CBType>
	inline ConstBufferObject<CBType>* ConstBufferObject<CBType>::Create(const bool isMutable)
	{
		ConstBufferObject* newConstBuffer = new ConstBufferObject();

		newConstBuffer->CreateBuffer(sizeof(CBType::Data), (void**)&newConstBuffer->map_, isMutable);

		return newConstBuffer;
	}

	template<typename CBType>
	void ConstBufferObject<CBType>::SetDrawCommand(const uint32_t rootParamIndex) 
	{
		// �l���X�V
		*map_ = data_;

		BaseConstBuffer::SetDrawCommand(rootParamIndex);
	}

	template<typename CBType>
	inline const std::string ConstBufferObject<CBType>::Tag() const
	{
		return CBType::Tag();
	}
}
