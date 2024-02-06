#include "Player.h"
#include "PlayerDrawer.h"
#include "CharacterConfig.h"

#include "GameObjectManager.h"

#include "CollisionDrawer.h"
#include "SphereCollider.h"
#include "Box2DCollider.h"

#include "StageManager.h"
#include "ScoreManager.h"
#include "WorldManager.h"

#include "MathVector.h"
#include "MathUtil.h"

#include "Keys.h"
#include "Pad.h"

#include <cassert>
#include <imgui.h>

using YGame::Player;
using YGame::WorldManager;
using YGame::GameCamera;
using YMath::Vector2;
using YMath::Vector3;
using YMath::BitFrag;
using YInput::Keys;
using YInput::Pad;

namespace
{
	WorldManager* pWorldMan = WorldManager::GetInstance();
	GameCamera* pCamera = nullptr;
}

void Player::StaticInitialize(GameCamera* pGameCamera)
{
	assert(pGameCamera);

	pCamera = pGameCamera;
}

std::unique_ptr<Player> Player::Create(
	const Transform::Status& status,
	const std::vector<std::string>& drawKeys)
{
	std::unique_ptr<Player> newObj = std::make_unique<Player>();

	newObj->Initialize(status);
	newObj->SetDrawKeys(drawKeys);

	return std::move(newObj);
}

void Player::Initialize(const Transform::Status& status)
{
	BaseCharacter::Initialize(
		"Player",
		status,
		{ +1.0f, 0.0f, 0.0f }, // 右向き
		PlayerConfig::kAcceleration, PlayerConfig::kMaxSpeed, true,
		PlayerConfig::kHP, PlayerConfig::kAttack, PlayerConfig::kInvincibleTime);

	ScoreManager::GetInstance()->SetMaxHP(PlayerConfig::kHP);
	ScoreManager::GetInstance()->SetHP(PlayerConfig::kHP);

	BitFrag attribute{};
	attribute.SetFragTrue(AttributeType::ePlayer);

	SetCollider(GameCollider::Create(attribute));
	
	SetIsSaveColl(true);

	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::eBlock);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&worldPos_, speed_.VelocityPtr(), PlayerConfig::kPhysicsRect, Vector3(), true, false),
			mask);
	}

	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::eGate);
		mask.SetFragTrue(AttributeType::eGoal);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&worldPos_, PlayerConfig::kPhysicsRect),
			mask);
	}

	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::eEnemy);
		mask.SetFragTrue(AttributeType::eEnemyAttack);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&worldPos_, speed_.VelocityPtr(), PlayerConfig::kCollRect, Vector3(), false, false),
			mask);
	}

	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::eCoin);
		mask.SetFragTrue(AttributeType::eItem);

		collider_->PushBackCollider(
			std::make_unique<YMath::SphereCollider>(
				&worldPos_, PlayerConfig::kRadius),
			mask);
	}

	collider_->SetPriority(1);


	SetDrawer(PlayerDrawer::Create(nullptr, nullptr, 1));

	jumpCounter_ = 0;

	maxJumpCount_ = PlayerConfig::kMaxJumpCount;

	isLanding_ = false;
	isElderLanding_ = false;
	
	pCamera->SetPlayerPosPtr(&transform_->pos_);
	
	// 立ちアニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eIdle), true);
}


void Player::UpdateControl()
{
	// 自動で前に進む
	moveDirection_.x = +1.0f;
	direction_ = Vector3(+1.0f, 0.0f, 0.0f);

	if (Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
		Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_A))
	{
		Jump();
	}

	if (Keys::GetInstance()->IsDown(DIK_V) ||
		Pad::GetInstance()->IsDown(YInput::PadButton::XIP_X))
	{
		Drop();
	}
}

void Player::UpdatePos()
{
	localPos_ += speed_.Velocity();

	worldPos_ = initPos_ + localPos_;
	
	//pWorldMan->SetMileage(pWorldMan->CurrentWorldKey(), localPos_);

	//transform_->pos_ = initPos_;
	transform_->pos_ = worldPos_;
}

void Player::UpdateBeforeCollision()
{
	BaseCharacter::UpdateBeforeCollision();
}

void Player::UpdateAfterCollision()
{
	BaseCharacter::UpdateAfterCollision();

	// 着地しているなら
	if (isLanding_)
	{
		// ジャンプ回数初期化
		jumpCounter_ = 0;

		// 瞬間
		if (isElderLanding_ == false)
		{
			// 着地アニメーション
			drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eLanding), true);

			// 移動アニメーション
			drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eMove), false);
		}
	}
	// 離陸した瞬間
	else if (isElderLanding_)
	{
		// 移動アニメーションをやめる
		drawer_->StopAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eMove));
	}

	isElderLanding_ = isLanding_;

	ScoreManager::GetInstance()->SetHP(status_.HP());
}

YGame::InfoOnCollision Player::GetInfoOnCollision()
{
	InfoOnCollision result = BaseCharacter::GetInfoOnCollision();

	result.attribute = AttributeType::ePlayer;
	result.radius = PlayerConfig::kRadius;

	return result;
}

void Player::Jump(const bool isJumpCount)
{
	// ジャンプカウントするなら
	if (isJumpCount)
	{
		// ジャンプ回数 が 最大回数超えてたら 弾く
		if (jumpCounter_ >= maxJumpCount_) { return; }

		jumpCounter_++;

		isLanding_ = false;
	}

	moveDirection_.y = 0.0f;
	speed_.VelocityRef().y = PlayerConfig::kJumpSpeed;

	// ジャンプアニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eJump), true);

	pCamera->MoveOnJump();
}

void Player::Drop()
{
	moveDirection_.y = -1.0f;

	// ジャンプアニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eJump), true);

	pCamera->MoveOnJump();
}

void Player::OffScreenProcess()
{
	// 画面外なら死ぬ
	if (YMath::InRange(initPos_ + localPos_, -YGame::kMaxWorldSize, YGame::kMaxWorldSize) == false)
	{
		StageManager::GetInstance()->GameOver();
	}
}

void Player::OnCollision(const InfoOnCollision& info)
{
	// 敵
	if (info.attribute == AttributeType::eEnemy)
	{
		// 自分 が 敵 より上にいる なら
		if (transform_->pos_.y - (PlayerConfig::kRadius / 4.0f) >= info.pTrfm->pos_.y + (info.radius / 4.0f))
		{
			pCamera->Shaking(1.0f, 0.2f, 100.0f);

			// ジャンプ
			Jump(false);
		}
		// 自分 が 敵 より下 なら
		else
		{
			// ダメージを受ける
			status_.Damage(info.pStatus->Attack(), true);

			if (status_.IsAlive() == false)
			{
				// 死亡アニメーション
				drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eDead), true);

				pCamera->SetPlayerPosPtr(nullptr);
				StageManager::GetInstance()->GameOver();
			}

			pCamera->Shaking(2.0f, 0.2f, 100.0f);

			// 被弾アニメーション
			drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eHit), true);
		}
	}
	// ブロック
	else if (info.attribute == AttributeType::eBlock)
	{
		if (transform_->pos_.y <= info.pTrfm->pos_.y) { return; }

		// 着地
		isLanding_ = true;
	}
	// ゲート
	else if (info.attribute == AttributeType::eGate)
	{
		if (status_.IsInvincible()) { return; }

		status_.ActivateInvincible();

 		speed_.SetMax(speed_.Max() * 1.2f);

		ScoreManager::GetInstance()->AddSpeedLevel();
		
		pCamera->MoveOnAccel();
	}
	// ゴール
	else if (info.attribute == AttributeType::eGoal)
	{
		StageManager::GetInstance()->ClearStage();
	}
}

void Player::DrawDebugTextContent()
{
	BaseCharacter::DrawDebugTextContent();
}
