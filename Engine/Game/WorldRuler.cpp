#include "WorldRuler.h"
#include <cassert>
#include <cmath>

using YGame::WorldRuler;
using YGame::WorldRuleAdopter;

// 時間スピード (デフォルト)
static const float DefTimeSpd_ = 1.0f;
// 重力 (デフォルト)
static const float DefGravity_ = 0.3f;
// 慣性 (デフォルト)
static const float DefFriction_ = 0.5f;

void WorldRuler::Initailze()
{
	// デフォルト値で初期化
	timeSpd_ = DefTimeSpd_;
	gravity_ = DefGravity_;
	friction_ = DefFriction_;

	// リセット
	Reset();
}

void WorldRuler::Reset()
{
	// 初期化
	isModify_ = false;

	modifyCount_ = 0;
	modifyFrame_ = 0;

	timeSpdEas_. Initialize(0.0f, 0.0f, 0.0f);
	gravityEas_. Initialize(0.0f, 0.0f, 0.0f);
	frictionEas_.Initialize(0.0f, 0.0f, 0.0f);
}

void WorldRuler::Update()
{
	// 修正中のみ
	if (isModify_ == false) { return; }

	// カウント
	modifyCount_++;
	// 比率
	float ratio = static_cast<float>(modifyCount_) / static_cast<float>(modifyFrame_);

	// 修正 (イージング)
	timeSpd_	 = timeSpdEas_. Out(ratio);
	gravity_	 = gravityEas_. Out(ratio);
	friction_	 = frictionEas_.Out(ratio);

	// 時間になったら
	if (modifyCount_ >= modifyFrame_)
	{
		// 初期化
		Initailze();
	}
}

void WorldRuler::Modify(const unsigned int time, const float exponent)
{
	// リセット
	Reset();

	// 代入
	modifyFrame_ = time;

	timeSpdEas_. Initialize(timeSpd_,  DefTimeSpd_,  exponent);
	gravityEas_. Initialize(gravity_,  DefGravity_,  exponent);
	frictionEas_.Initialize(friction_, DefFriction_, exponent);
}

void WorldRuler::SetTimeSpeed(const float timeSpd)
{
	// 0以下にならないように
	timeSpd_ = fmaxf(timeSpd, 0.0f);
}

void WorldRuler::SetGravity(const float gravity)
{
	// 0以下にならないように
	gravity_ = fmaxf(gravity, 0.0f);
}

void WorldRuler::SetFriction(const float friction)
{
	// 0以下にならないように
	friction_ = fmaxf(friction, 0.0f);
}

WorldRuler* WorldRuleAdopter::spWorldRuler_ = nullptr;

void WorldRuleAdopter::StaticInitialize(WorldRuler* pWorldRuler)
{
	// nullチェック
	assert(pWorldRuler);

	// 代入
	spWorldRuler_ = pWorldRuler;
}
