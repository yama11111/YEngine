#include "Power.h"
#include <cmath>

using YMath::Power;

Power::Power(const uint32_t maxPower) : 
	current_(0),
	maxPower_(static_cast<float>(maxPower))
{	
}

void Power::Initialize(const uint32_t maxPower)
{
	// ���
	SetMaxPower(maxPower);

	// ���Z�b�g
	Reset();
}

void Power::Reset()
{
	// ������
	current_ = 0;
}

void Power::Update(const bool isAct)
{
	// ���Z�l
	float spd = 1.0f;

	// ���쒆�Ȃ�
	if (isAct)
	{
		// ���Z (�ő�l�𒴂��Ȃ��悤��)
		current_ = fminf(current_ + spd, maxPower_);
	}
	else
	{
		// ���Z (0.0f�𒴂��Ȃ��悤��)
		current_ = fmaxf(current_ - spd, 0.0f);
	}
}

float Power::Ratio()
{
	// 0�Ŋ���Ȃ��悤��
	if (maxPower_ == 0) { return 0.0f; }
	return current_ / maxPower_;
}

void Power::SetMaxPower(const uint32_t maxPower)
{
	maxPower_ = static_cast<float>(maxPower);
}
