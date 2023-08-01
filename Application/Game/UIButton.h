#pragma once
#include "BaseDrawObject.h"

namespace YGame
{
	class UIButton
	{

	public:

		/// <summary>
		/// ���I�C���X�^���X����
		/// </summary>
		/// <param name="obj"> : �I�u�W�F�N�g (���I�C���X�^���X)</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		/// <returns>���I�C���X�^���X</returns>
		static UIButton* Create(BaseDrawObject* obj, const bool isClearWhenTransition = true);

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="obj"> : �I�u�W�F�N�g (���I�C���X�^���X)</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		virtual void Initialize(BaseDrawObject* obj, const bool isClearWhenTransition = true) = 0;

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="isDown"> : �����Ă��邩</param>
		virtual void Update(const bool isDown) = 0;
		
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="shaderTag"> : �V�F�[�_�[�^�O</param>
		/// <param name="priority"> : �`��D��x</param>
		virtual void Draw(const std::string& shaderTag, const uint16_t priority) = 0;
	
	public:

		UIButton() = default;
		
		virtual ~UIButton() = default;

	};
}
