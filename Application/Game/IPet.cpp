#include "IPet.h"
#include "MapChipCollisionBitConfig.h"
#include "CharacterConfig.h"

#include "SceneExecutive.h"

#include <cassert>

using YGame::IPet;
using YMath::Vector3;
using YInput::Keys;
using YInput::Pad;

YGame::ScrollCamera* IPet::spScrollCamera_ = nullptr;

void IPet::Update(const bool isUpdate)
{
	if (isUpdate)
	{
		// 自動で前に進む
		moveDirection_ += Vector3(+1.0f, 0.0f, 0.0f);
		direction_ = Vector3(+1.0f, 0.0f, 0.0f);
	}

	BaseCharacter::Update(isUpdate);

	// 着地しているなら
	if (MapChipCollider::CollisionBit() & ChipCollisionBit::kBottom)
	{
		// ジャンプ回数初期化
		jumpCounter_ = 0;
	}
}

void IPet::OnCollision(const CollisionInfo& info)
{
	if (isRidden_ == false) { return; }

	// 敵
	if (info.attribute_ == AttributeType::eEnemy)
	{
		// 自分 が 敵 より上にいる なら
		if (transform_->pos_.y_ - (PetConfig::kRadius / 2.0f) >= info.pos_.y_ + (info.radius_ / 2.0f))
		{
			// ダメージを与える
			info.pStatus_->Damage(status_.Attack(), true);

			spScrollCamera_->Shaking(1.0f, 0.2f, 100.0f);
			
			// ジャンプ
			Jump(false);
		}
		// 自分 が 敵 より下 なら
		else
		{
			Hit();
		}

		return;
	}
}

void IPet::Rideen()
{
	isRidden_ = true;
	
	isHit_ = false;

	spScrollCamera_->SetFollowPoint(&transform_->pos_);

	speed_.SetAcceleration(PetConfig::kNormalAcceleration);
	speed_.SetMax(PetConfig::kNormalMaxSpeed);
}

void IPet::GotOff()
{
	isRidden_ = false;

	speed_.SetAcceleration(PetConfig::kRunAcceleration);
	speed_.SetMax(PetConfig::kRunMaxSpeed);
}

void IPet::StaticInitialize(ScrollCamera* pScrollCamera)
{
	assert(pScrollCamera);

	spScrollCamera_ = pScrollCamera;
}

void IPet::Hit()
{
	isHit_ = true;

	spScrollCamera_->Shaking(2.0f, 0.2f, 100.0f);
}

void IPet::OffScreenProcess()
{
	if (isRidden_ == false) { return; }

	if (YGame::TransitionManager::GetInstance()->IsAct()) { return; }

	YGame::SceneExecutive::GetInstance()->Change(
		"PLAY", "BLACKOUT", 10, 5
	);
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
}
