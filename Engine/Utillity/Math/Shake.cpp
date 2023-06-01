#include "Shake.h"
#include "MathUtillity.h"

using YMath::Shake;

void Shake::Initialize()
{
	// ������
	isAct_ = false;
	swing_ = 0.0f;
	dekey_ = 0.0f;
	place_ = 0.0f;
	value_ = {};
}

void Shake::Activate(const float swing, const float dekey, const float place)
{
	// ���삵�Ă��Ȃ��Ȃ�
	if (!isAct_)
	{
		// ������ + ���
		dekey_ = dekey;
		swing_ = swing;
		place_ = place;
		value_ = {};

		// ����J�n
		isAct_ = true;
	}
	// �h��ʂ������傫���Ȃ�
	else if (swing_ <= swing)
	{
		// ���
		dekey_ = dekey;
		swing_ = swing;
		place_ = place;
	}
}

void Shake::Update()
{
	// �͈͂�0�ȏ�Ȃ�
	if (swing_ > 0) 
	{
		// �͈͂����߂�
		swing_ -= dekey_; 
	}
	// ����ȊO�Ȃ�
	else
	{
		// ������
		Initialize();
	}

	// ���쒆�Ȃ�
	if (isAct_)
	{
		// �͈͓��̗�������
		value_.x_ = GetRand(-swing_, swing_, place_);
		value_.y_ = GetRand(-swing_, swing_, place_);
		value_.z_ = GetRand(-swing_, swing_, place_);
	}
}
