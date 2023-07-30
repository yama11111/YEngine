#include "Timer.h"
#include <cmath>

using YMath::Timer;

Timer::Timer(const uint32_t endFrame, const bool isAct) :
	current_(0),
	endFrame_(endFrame),
	isAct_(isAct)
{
}

void Timer::Initialize(const uint32_t endFrame, const bool isAct)
{
	// ���
	SetEndFrame(endFrame);

	// ���Z�b�g
	Reset(isAct);
}

void Timer::Reset(const bool isAct)
{
	// ������
	current_ = 0;
	isAct_ = isAct;
}

void Timer::Update(const float passRate)
{
	// ���쒆�̂ݒʂ�
	if (isAct_ == false) { return; }

	// ���Z�l
	float spd = 1.0f * passRate;

	// ���Z
	current_ += spd;
	
	// ���ԂɂȂ�����
	if (current_ >= static_cast<float>(endFrame_))
	{
		// �I������
		current_ = static_cast<float>(endFrame_);
		isAct_ = false;
	}
}

float Timer::Ratio()
{
	// 0�Ŋ���Ȃ��悤��
	if (endFrame_ == 0) { return 0.0f; }
	return current_ / static_cast<float>(endFrame_);
}