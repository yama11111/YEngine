#pragma once
#include "BaseConstBuffer.h"
#include <memory>

namespace YGame
{
	// �萔�o�b�t�@
	template<typename CBData>
	class ConstBufferSet final
	{

	public:

		// �f�[�^
		CBData data_;

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <returns>���I�C���X�^���X</returns>
		static ConstBufferSet* Create(const bool isMutable = true);

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="data">�萔�o�b�t�@�f�[�^</param>
		/// <returns>���I�C���X�^���X</returns>
		static ConstBufferSet* Create(const CBData& data, const bool isMutable = true);

	public:

		/// <summary>
		/// �萔�o�b�t�@�{�̂̃|�C���^���擾
		/// </summary>
		/// <returns>�萔�o�b�t�@�{�̂̃|�C���^</returns>
		BaseConstBuffer* ConstBufferPtr();

	public:

		ConstBufferSet() = default;

		~ConstBufferSet() = default;

		// ���n �� �֎~
		ConstBufferSet(const ConstBufferSet&) = delete;

		const ConstBufferSet& operator=(const ConstBufferSet&) = delete;
	
	private:

		// �萔�o�b�t�@�{��
		std::unique_ptr<BaseConstBuffer> cBuff_;
	};

	template<typename CBData>
	inline ConstBufferSet<CBData>* ConstBufferSet<CBData>::Create(const bool isMutable)
	{
		ConstBufferSet* newCB = new ConstBufferSet();

		// �萔�o�b�t�@�{�̂𐶐�
		newCB->cBuff_.reset(BaseConstBuffer::Create<CBData>(&newCB->data_, isMutable));

		return newCB;
	}
	template<typename CBData>
	inline ConstBufferSet<CBData>* ConstBufferSet<CBData>::Create(const CBData& data, const bool isMutable)
	{
		ConstBufferSet* newCB = ConstBufferSet();

		// �萔�o�b�t�@�{�̂𐶐�
		newCB->cBuff_.reset(BaseConstBuffer::Create<CBData>(&newCB->data_, isMutable));

		newCB->SetData(data);

		return newCB;
	}
	template<typename CBData>
	inline BaseConstBuffer* ConstBufferSet<CBData>::ConstBufferPtr()
	{
		return cBuff_.get();
	}
}
