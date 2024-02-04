#include "Player.h"
#include "PlayerDrawer.h"
#include "CharacterConfig.h"

#include "GameObjectManager.h"
#include "NeedleAttack.h"

#include "CollisionDrawer.h"
#include "SphereCollider.h"
#include "Box2DCollider.h"

#include "StageManager.h"
#include "ScoreManager.h"

#include "Keys.h"
#include "Pad.h"

#include <cassert>
#include <imgui.h>

using YGame::Player;
using YMath::Vector2;
using YMath::Vector3;
using YMath::BitFrag;
using YInput::Keys;
using YInput::Pad;

YGame::GameCamera* Player::spCamera_ = nullptr;

void Player::StaticInitialize(GameCamera* pCamera)
{
	assert(pCamera);

	spCamera_ = pCamera;
}

std::unique_ptr<Player> Player::Create(const Transform::Status& status)
{
	std::unique_ptr<Player> newObj = std::make_unique<Player>();

	newObj->Initialize(status);

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

	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::eBlock);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&transform_->pos_, speed_.VelocityPtr(), PlayerConfig::kRectSize, Vector3(), true, false),
			mask);
	}

	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::eGate);
		mask.SetFragTrue(AttributeType::eGoal);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&transform_->pos_, PlayerConfig::kRectSize),
			mask);
	}

	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::eEnemy);
		mask.SetFragTrue(AttributeType::eEnemyAttack);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&transform_->pos_, speed_.VelocityPtr(), PlayerConfig::kRectSize, Vector3(), false, false),
			mask);
	}
	
	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::eCoin);
		mask.SetFragTrue(AttributeType::eItem);
		
		collider_->PushBackCollider(
			std::make_unique<YMath::SphereCollider>(
				&transform_->pos_, PlayerConfig::kRadius), 
			mask);
	}

	collider_->SetPriority(1);

	SetDrawer(PlayerDrawer::Create(nullptr, 1));

	jumpCounter_ = 0;

	maxJumpCount_ = PlayerConfig::kMaxJumpCount;

	isLanding_ = false;
	isElderLanding_ = false;
	
	spCamera_->SetPlayerPosPtr(&transform_->pos_);
	
	// 立ちアニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eIdle), true);
}

void Player::UpdateControl()
{
	// 自動で前に進む
	moveDirection_ += Vector3(+1.0f, 0.0f, 0.0f);
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

	speed_.VelocityRef().y_ = PlayerConfig::kJumpSpeed;

	// ジャンプアニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eJump), true);

	spCamera_->MoveOnJump();
}

void Player::Drop()
{
	if (isLanding_) { return; }

	moveDirection_.y_ = -1.0f;

	// ジャンプアニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eJump), true);

	spCamera_->MoveOnJump();
}

void Player::Attack()
{
	// 攻撃新規生成
	GameObjectManager::GetInstance()->PushBack(
		NeedleAttack::Create(
			NeedleAttackConfig::kAliveTime,
			transform_->pos_ + Vector3(+5.0f, 0.0f, 0.0f),
			NeedleAttackConfig::kAcceleration,
			NeedleAttackConfig::kMaxSpeed,
			NeedleAttackConfig::kRadius,
			NeedleAttackConfig::kPower), 0, true, true);

	// 攻撃アニメーション
	drawer_->PlayAnimation(
		static_cast<uint32_t>(PlayerDrawer::AnimationType::eAttack), true);
}

void Player::OffScreenProcess()
{
	StageManager::GetInstance()->GameOver();
}

void Player::OnCollision(const InfoOnCollision& info)
{
	// 敵
	if (info.attribute == AttributeType::eEnemy)
	{
		// 自分 が 敵 より上にいる なら
		if (transform_->pos_.y_ - (PlayerConfig::kRadius / 4.0f) >= info.pTrfm->pos_.y_ + (info.radius / 4.0f))
		{
			spCamera_->Shaking(1.0f, 0.2f, 100.0f);

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

				spCamera_->SetPlayerPosPtr(nullptr);
				StageManager::GetInstance()->GameOver();
			}

			spCamera_->Shaking(2.0f, 0.2f, 100.0f);

			// 被弾アニメーション
			drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eHit), true);
		}
	}
	// ブロック
	else if (info.attribute == AttributeType::eBlock)
	{
		if (transform_->pos_.y_ <= info.pTrfm->pos_.y_) { return; }

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
		
		spCamera_->MoveOnAccel();
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
