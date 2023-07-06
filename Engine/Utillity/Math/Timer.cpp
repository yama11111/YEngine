#include "Timer.h"
#include <cmath>

using YMath::Timer;

Timer::Timer(const uint32_t endFrame, const bool isAct) :
	current_(0),
	endFrame_(static_cast<float>(endFrame)),
	isAct_(isAct)
{
}

void Timer::Initialize(const uint32_t endFrame, const bool isAct)
{
	// ���
	SetEndFrame(endFrame);

	// ���Z�b�g
	Reset(false);
}

void Timer::Reset(const bool isAct)
{
	// ������
	current_ = 0;
	isAct_ = isAct;
}

void Timer::Update()
{
	// ���쒆�̂ݒʂ�
	if (isAct_ == false) { return; }

	// ���Z�l (�K�p����Ȃ玞�ԃX�s�[�h��Z)
	float spd = 1.0f;

	// ���Z
	current_ += spd;
	
	// ���ԂɂȂ�����
	if (current_ >= endFrame_)
	{
		// �I������
		current_ = endFrame_;
		isAct_ = false;
	}
}

float Timer::Ratio()
{
	// 0�Ŋ���Ȃ��悤��
	if (endFrame_ == 0) { return 0.0f; }
	return current_ / endFrame_;
}

void Timer::SetEndFrame(const uint32_t endFrame)
{
	// �L���X�g���đ��
	endFrame_ = static_cast<float>(endFrame);
}