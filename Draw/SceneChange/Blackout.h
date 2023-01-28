#pragma once
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"
#include "Sprite.h"

namespace YTransition
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
		YGame::Object curten_;
		// �^�C�}�[
		int count_ = 0;
		// �C�[�W���O
		YMath::Ease<float> blendE_;
		YMath::Power blendP_;

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
			YGame::Sprite* curtenSprite_;
		};
	private:
		static YGame::Sprite* curtenS_;
	public:
		// �ÓI������
		static void StaticInitialize(const StaticInitStatus& state);
	};
}
