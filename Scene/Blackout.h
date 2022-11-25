#pragma once
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"
#include "Sprite.h"

namespace Transition
{
	class Blackout
	{
	private:
		// �Ó]�i�K
		enum class Step
		{
			Dark, // ��
			Load, // ���[�h����
			Bright, // ��
		};
	private:
		// �i�K
		Step boStep_ = Step::Dark;
		// �I�u�W�F�N�g
		Game::Object curten_;
		// �^�C�}�[
		int count_ = 0;
		// �C�[�W���O
		Math::Ease<float> blendE_;
		Math::Power blendP_;

		// ���쒆
		bool isAct_ = false;
		// �؂�ւ��̏u��
		bool isChangeMoment_ = false;
	public:
		// ������
		void Initialize();
		// �X�V
		void Update();
		// �`��
		void Draw();
	public:
		// ����J�n
		void Activate();
		// �؂�ւ��̏u��
		bool IsChangeMoment() { return isChangeMoment_; }
	private:
		void ChangeUpdate();
		void BlendUpdate();
	public:
		struct StaticInitStatus
		{
			Game::Sprite* curtenSprite_;
		};
	private:
		static Game::Sprite* curtenS_;
	public:
		// �ÓI������
		static void StaticInitialize(const StaticInitStatus& state);
	};
}
