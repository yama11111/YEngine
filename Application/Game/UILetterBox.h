#pragma once
#include "DrawObjectForSprite2D.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "Ease.h"
#include "Timer.h"
#include <array>

namespace YGame
{
	class UILetterBox final
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="winSize"> : �E�B���h�E�T�C�Y</param>
		/// <param name="topHeight"> : ��̍���</param>
		/// <param name="bottomHeight"> : ���̍���</param>
		void Initialize(const YMath::Vector2& winSize, const float topHeight, const float bottomHeight);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// ���낷
		/// </summary>
		/// <param name="frame"></param>
		/// <param name="exponent"></param>
		void Drop(const uint32_t frame, const float exponent);

		/// <summary>
		/// ���܂�
		/// </summary>
		/// <param name="frame"></param>
		/// <param name="exponent"></param>
		void Close(const uint32_t frame, const float exponent);

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="shaderTag"> : �V�F�[�_�[�^�O</param>
		/// <param name="priority"> : �`��D��x</param>
		void Draw(const std::string& shaderTag, const uint16_t priority);
	
	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void LoadResource();
	
	private:

		// ���
		enum class State
		{
			None, // �������Ă��Ȃ�

			Drop, // ���낵�Ă���

			Close,  // ���܂��Ă���
		};
	
	private:

		// �X�v���C�g�I�u�W�F�N�g
		std::array<std::unique_ptr<DrawObjectForSprite2D>, 2> objs_;

		// �F
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// �����C�[�W���O�p�^�C�}�[
		YMath::Timer heightEasTimer_;

		// �����C�[�W���O
		std::array<YMath::Ease<YMath::Vector3>, 2> heightEas_;

		// ���݂̏��
		State state = State::None;

	private:

		// �ÓI�X�v���C�g
		static Sprite2D* spSpr_;

	private:

		/// <summary>
		/// �ʒu�X�V
		/// </summary>
		void UpdatePos();
	};
}
