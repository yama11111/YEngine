#include "WorldRuler.h"
#include <cassert>
#include <cmath>

using YGame::WorldRuler;
using YGame::WorldRuleAdopter;

// ���ԃX�s�[�h (�f�t�H���g)
static const float DefTimeSpd_ = 1.0f;
// �d�� (�f�t�H���g)
static const float DefGravity_ = 0.3f;
// ���� (�f�t�H���g)
static const float DefFriction_ = 0.5f;

void WorldRuler::Initailze()
{
	// �f�t�H���g�l�ŏ�����
	timeSpd_ = DefTimeSpd_;
	gravity_ = DefGravity_;
	friction_ = DefFriction_;

	// ���Z�b�g
	Reset();
}

void WorldRuler::Reset()
{
	// ������
	isModify_ = false;

	modifyCount_ = 0;
	modifyFrame_ = 0;

	timeSpdEas_. Initialize(0.0f, 0.0f, 0.0f);
	gravityEas_. Initialize(0.0f, 0.0f, 0.0f);
	frictionEas_.Initialize(0.0f, 0.0f, 0.0f);
}

void WorldRuler::Update()
{
	// �C�����̂�
	if (isModify_ == false) { return; }

	// �J�E���g
	modifyCount_++;
	// �䗦
	float ratio = static_cast<float>(modifyCount_) / static_cast<float>(modifyFrame_);

	// �C�� (�C�[�W���O)
	timeSpd_	 = timeSpdEas_. Out(ratio);
	gravity_	 = gravityEas_. Out(ratio);
	friction_	 = frictionEas_.Out(ratio);

	// ���ԂɂȂ�����
	if (modifyCount_ >= modifyFrame_)
	{
		// ������
		Initailze();
	}
}

void WorldRuler::Modify(const unsigned int time, const float exponent)
{
	// ���Z�b�g
	Reset();

	// ���
	modifyFrame_ = time;

	timeSpdEas_. Initialize(timeSpd_,  DefTimeSpd_,  exponent);
	gravityEas_. Initialize(gravity_,  DefGravity_,  exponent);
	frictionEas_.Initialize(friction_, DefFriction_, exponent);
}

void WorldRuler::SetTimeSpeed(const float timeSpd)
{
	// 0�ȉ��ɂȂ�Ȃ��悤��
	timeSpd_ = fmaxf(timeSpd, 0.0f);
}

void WorldRuler::SetGravity(const float gravity)
{
	// 0�ȉ��ɂȂ�Ȃ��悤��
	gravity_ = fmaxf(gravity, 0.0f);
}

void WorldRuler::SetFriction(const float friction)
{
	// 0�ȉ��ɂȂ�Ȃ��悤��
	friction_ = fmaxf(friction, 0.0f);
}

WorldRuler* WorldRuleAdopter::spWorldRuler_ = nullptr;

void WorldRuleAdopter::StaticInitialize(WorldRuler* pWorldRuler)
{
	// null�`�F�b�N
	assert(pWorldRuler);

	// ���
	spWorldRuler_ = pWorldRuler;
}
