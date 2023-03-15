#include "Timer.h"

using YMath::Timer;

void Timer::Initialize(const unsigned int end, const bool isApply)
{
	// ���
	end_ = static_cast<float>(end);
	isApply_ = isApply;

	// ���Z�b�g
	Reset(false);
}

void Timer::Reset(const bool isAct)
{
	// ������
	count_ = 0;
	isAct_ = isAct;
}

void Timer::Update()
{
	// ���쒆�̂ݒʂ�
	if (isAct_ == false) { return; }

	// ���Z�l (�K�p����Ȃ玞�ԃX�s�[�h��Z)
	float spd = 1.0f;
	if (isApply_) { spd *= spWorldRuler_->GetTimeSpeed(); }

	// ���Z
	count_ += spd;
	
	// ���ԂɂȂ�����
	if (count_ >= end_)
	{
		// �I������
		count_ = end_;
		isAct_ = false;
	}
}

float Timer::Ratio()
{
	// 0�Ŋ���Ȃ��悤��
	if (end_ == 0) { return 0.0f; }
	return count_ / end_;
}
