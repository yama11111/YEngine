#pragma once
#include <cstdint>
#include <string>

namespace YGame
{
	class BaseConstBuffer
	{

	public:
		
		/// <summary>
		/// �萔�o�b�t�@�̐��� + �}�b�s���O
		/// </summary>
		/// <param name="pCBData"> : �萔�o�b�t�@�f�[�^�|�C���^</param>
		/// <param name="isMutable"> : ���Z�b�g���邩</param>
		template<typename CBData>
		static BaseConstBuffer* Create(CBData* pCBData, const bool isMutable = true);

	public:

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="rootParamIndex"> : ���[�g�p�����[�^�ԍ�</param>
		virtual void SetDrawCommand(const uint32_t rootParamIndex) = 0;
		
		/// <summary>
		/// �L�[�̖��O�擾
		/// </summary>
		/// <returns>�L�[�̖��O</returns>
		virtual const std::string KeyName() const = 0;
	
	public:
	
		virtual ~BaseConstBuffer() = default;
	
	protected:

		/// <summary>
		/// �R���X�g���N�^ (�ʏ�̐錾���֎~����)
		/// </summary>
		BaseConstBuffer() = default;

	};
}
