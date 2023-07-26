#pragma once
#include "BaseConstBuffer.h"
#include "BaseGraphic.h"

namespace YGame
{
	class Object
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		void Clear();

	public:

		/// <summary>
		/// �萔�o�b�t�@�|�C���^�擾
		/// </summary>
		/// <returns>�萔�o�b�t�@�|�C���^</returns>
		YDX::BaseConstBuffer* ConstBufferPtr(const std::string& key);

		/// <summary>
		/// �O���t�B�b�N�|�C���^
		/// </summary>
		/// <returns></returns>
		BaseGraphic* GraphicPtr() const;

	public:

		/// <summary>
		/// �萔�o�b�t�@�}�� 
		/// (������ނ̒萔�o�b�t�@�����������ւ���)
		/// </summary>
		/// <param name="pCBuff"> : �萔�o�b�t�@�|�C���^</param>
		void InsertConstBuffer(YDX::BaseConstBuffer* pCBuff);

		/// <summary>
		/// �O���t�B�b�N�ݒ�
		/// </summary>
		/// <param name="pGraphic"> : �O���t�B�b�N�|�C���^</param>
		void SetGraphic(BaseGraphic* pGraphic);

	protected:

		// �萔�o�b�t�@�}�b�v
		std::unordered_map<std::string, YDX::BaseConstBuffer*> cbPtrMap_;

		// �O���t�B�b�N
		BaseGraphic* pGraphic_ = nullptr;
	};
}
