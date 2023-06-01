#include "Power.h"
#include <cmath>

using YMath::Power;

void Power::Initialize(const unsigned int max, const bool isApply)
{
	// ���
	max_ = static_cast<float>(max);
	isApply_ = isApply;

	// ���Z�b�g
	Reset();
}

void Power::Reset()
{
	// ������
	count_ = 0;
}

void Power::Update(const bool isAct)
{
	// ���Z�l (�K�p����Ȃ玞�ԃX�s�[�h��Z)
	float spd = 1.0f;
	if (isApply_) { spd *= spWorldRuler_->GetTimeSpeed(); }

	// ���쒆�Ȃ�
	if (isAct)
	{
		// ���Z (�ő�l�𒴂��Ȃ��悤��)
		count_ = fminf(count_ + spd, max_);
	}
	else
	{
		// ���Z (0.0f�𒴂��Ȃ��悤��)
		count_ = fmaxf(count_ - spd, 0.0f);
	}
}

float Power::Ratio()
{
	// 0�Ŋ���Ȃ��悤��
	if (max_ == 0) { return 0.0f; }
	return count_ / max_;
}