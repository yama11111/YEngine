#pragma once
#pragma once
#include "BaseConstBuffer.h"
#include <unordered_map>

namespace YGame
{
	// �萔�o�b�t�@�|�C���^�Z�b�g�N���X
	class ConstBufferPtrSet final
	{

	public:

		/// <summary>
		/// �N���A
		/// </summary>
		void Clear();

		/// <summary>
		/// �萔�o�b�t�@�|�C���^�}�� 
		/// (������ނ̒萔�o�b�t�@�����������ւ���)
		/// </summary>
		/// <param name="pCBuff"> : �萔�o�b�t�@�|�C���^</param>
		void Insert(BaseConstBuffer* pCB);
		
		/// <summary>
		/// �萔�o�b�t�@�|�C���^�}�� (�f�t�H���g)
		/// (������ނ̒萔�o�b�t�@�����������ւ���)
		/// </summary>
		/// <param name="cbTag"> : �萔�o�b�t�@�^�O</param>
		void InsertDefault(const std::string& tag);

		/// <summary>
		/// �`��R�}���h
		/// </summary>
		/// <param name="tag"> : �^�O</param>
		/// <param name="rpIndex"> : ���[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(const std::string& tag, const uint32_t rpIndex);

	private:

		// �}�b�v
		std::unordered_map<std::string, BaseConstBuffer*> cbPtrMap_;
	};
}
