#pragma once
#include "Shake.h"
#include "Vector4.h"

namespace YActor
{
	class HitActor
	{
	private:
		// �����Ă��邩�t���O
		bool isAct_ = false;
		// �h��
		YMath::Shake shake_;
		// �F
		YMath::Vector4 color_;
		// �`�J�`�J�t���O
		bool isFliclering_ = false;
	public:
		// ������
		void InitializeHitAction();
		// ������
		void ActivateHitAction(const float shakeValue, const unsigned int frame);
		// �X�V
		void UpdateHitAction();
	public:
		// ���l�擾 (�h��)
		YMath::Vector3 HitActionShakeValue();
		// ���l�擾 (�F)
		YMath::Vector4 HitActionColor();
		// �����Ă��邩
		bool IsActHitAction() { return isAct_; }
	};
}
