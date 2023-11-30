#include "IPet.h"
#include "CharacterConfig.h"

#include "MapChipCollisionBitConfig.h"

#include "SceneManager.h"
#include "StageManager.h"

#include <cassert>

using YGame::IPet;
using YMath::Vector3;
using YInput::Keys;
using YInput::Pad;

YGame::GameCamera* IPet::spCamera_ = nullptr;

namespace
{
	IPet* spPet = nullptr;
}
void IPet::StaticSetPetPointer(IPet* pPet)
{
	spPet = pPet;
}
IPet* IPet::StaticGetPetPointer()
{
	return spPet;
}

void IPet::StaticInitialize(GameCamera* pCamera)
{
	assert(pCamera);

	spCamera_ = pCamera;
}

void IPet::UpdateBeforeCollision()
{
	BaseCharacter::UpdateBeforeCollision();
}

void IPet::UpdateAfterCollision()
{
	BaseCharacter::UpdateAfterCollision();

	// 着地しているなら
	//if ()
	//{
	//	// ジャンプ回数初期化
	//	jumpCounter_ = 0;
	//}

	jumpCounter_ = 0;
}

void IPet::Jump(const bool isJumpCount)
{
	// ジャンプカウントするなら
	if (isJumpCount)
	{
		// ジャンプ回数 が 最大回数超えてたら 弾く
		if (jumpCounter_ >= maxJumpCount_) { return; }

		jumpCounter_++;
	}

	speed_.VelocityRef().y_ = 0.0f;

	moveDirection_.y_ = 1.0f;

	spCamera_->MoveOnJump();
}

void IPet::Rideen()
{
	isRidden_ = true;
	
	isHit_ = false;

	spCamera_->SetPlayerPosPtr(&transform_->pos_);

	speed_.SetAcceleration(PetConfig::kNormalAcceleration);
	speed_.SetMax(PetConfig::kNormalMaxSpeed);
}

void IPet::GotOff()
{
	isRidden_ = false;

	//speed_.SetAcceleration(PetConfig::kRunAcceleration);
	//speed_.SetMax(PetConfig::kRunMaxSpeed);
}

void IPet::UpdateControl()
{
	// 自動で前に進む
	moveDirection_ += Vector3(+1.0f, 0.0f, 0.0f);
	direction_ = Vector3(+1.0f, 0.0f, 0.0f);
}

void IPet::OnCollision(const InfoOnCollision& info)
{
	if (isRidden_ == false) { return; }

	// 敵
	if (info.attribute == AttributeType::eEnemy)
	{
		// 自分 が 敵 より上にいる なら
		if (transform_->pos_.y_ - (PetConfig::kRadius / 4.0f) >= info.pTrfm->pos_.y_ + (info.radius / 4.0f))
		{
			spCamera_->Shaking(1.0f, 0.2f, 100.0f);

			// ジャンプ
			Jump(false);
		}
		// 自分 が 敵 より下 なら
		else
		{
			Hit();
		}
	}
	// ゴール
	else if (info.attribute == AttributeType::eGoal)
	{
		StageManager::GetInstance()->ClearStage();
	}
}

void IPet::Hit()
{
	isHit_ = true;

	status_.Damage(0, true);

	spCamera_->Shaking(2.0f, 0.2f, 100.0f);
}

void IPet::OffScreenProcess()
{
	if (isRidden_ == false) { return; }

	if (SceneManager::GetInstance()->IsTransition()) { return; }

	SceneManager::GetInstance()->Transition("PLAY", "WAVE");
}

