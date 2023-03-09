#pragma once
#include "Shake.h"
#include "Vector4.h"

namespace YGame
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
		void Initialize();
		// ������
		void Activate(const float shakeValue, const unsigned int frame);
		// �X�V
		void Update();
	public:
		// ���l�擾 (�h��)
		YMath::Vector3 ShakeValue();
		// ���l�擾 (�F)
		YMath::Vector4 ColorValue();
		// �����Ă��邩
		bool IsActHitAction() { return isAct_; }
	};
}
