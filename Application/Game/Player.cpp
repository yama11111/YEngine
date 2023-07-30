#include "Player.h"
#include "PlayerDrawer.h"
#include "PrimitiveCollider.h"
#include "MapChipCollisionBitConfig.h"

#include "CharacterConfig.h"
#include "AnimationConfig.h"

#include "CharacterManager.h"
#include "SlashAttack.h"

#include "SceneExecutive.h"

#include <cassert>
#include <imgui.h>

using YGame::Player;
using YMath::Vector3;
using YInput::Keys;
using YInput::Pad;

YGame::ScrollCamera* Player::spScrollCamera_ = nullptr;

void Player::Initialize(const Transform::Status& status, IPet* pPet)
{
	BaseCharacter::Initialize(
		"Player",
		status,
		{ +1.0f, 0.0f, 0.0f}, // 右向き
		PlayerConfig::kAcceleration, PlayerConfig::kMaxSpeed,
		PlayerConfig::kHP, PlayerConfig::kAttack, PlayerConfig::kInvincibleTime,
		new GameCollider(transform_.get(), AttributeType::ePlayer, AttributeType::eAll),
		PlayerDrawer::Create(nullptr, 1));

	collider_->PushBack(new YMath::SphereCollider(Vector3(), PlayerConfig::kRadius));

	jumpCounter_ = 0;

	maxJumpCount_ = PlayerConfig::kMaxJumpCount;

	// 開始時は武装する
	isArmed_ = true;

	RideOnPet(pPet);

	if (pPet_ == nullptr)
	{
		spScrollCamera_->SetFollowPoint(&transform_->pos_);
	}

	// 立ちアニメーション
	drawer_->PlayAnimation(
		static_cast<uint16_t>(PlayerDrawer::AnimationType::eIdle), 
		PlayerAnimationConfig::kIdleFrame
	);
}

void Player::RideOnPet(IPet* pPet)
{
	pPet_ = pPet;

	if (pPet_)
	{
		// 親子関係
		SetParent(pPet_);

		// 乗る位置分 上に移動
		transform_->pos_ = Vector3(0.0f, pPet_->RidingPosHeight(), 0.0f);
		transform_->UpdateMatrix();

		speed_.SetIsGravity(false);

		speed_.Reset();

		collider_->SetIsSlip(true);

		drawer_->SetParent(pPet_->DrawerPtr()->TransformPtr());
		drawer_->SetIsVisibleUpdate(false);

		pPet_->Rideen();

		// 移動アニメーションをやめる
		drawer_->AbortAnimation(static_cast<uint16_t>(PlayerDrawer::AnimationType::eMove));
	}
}

void Player::GetOffPet()
{
	pPet_->GotOff();

	transform_->pos_ += pPet_->PosRef();
	transform_->UpdateMatrix();

	pPet_ = nullptr;
	
	SetParent(nullptr);
	
	speed_.SetIsGravity(true);

	collider_->SetIsSlip(false);

	drawer_->SetParent(transform_.get());
	drawer_->SetIsVisibleUpdate(true);
	
	// 飛び降りる
	Jump(false);

	// カメラを自分追従に
	spScrollCamera_->SetFollowPoint(&transform_->pos_);

	// 移動アニメーション
	drawer_->PlayAnimation(
		static_cast<uint16_t>(PlayerDrawer::AnimationType::eMove), 
		PlayerAnimationConfig::Move::kFrame, 
		true
	);
}

void Player::Update()
{
	// ペットが被弾したら降りる
	if(pPet_)
	{
		if (pPet_->IsHit())
		{
			GetOffPet();
		}
	}

	if (pPet_ == nullptr)
	{
		// 自動で前に進む
		moveDirection_ += Vector3(+1.0f, 0.0f, 0.0f);
		direction_ = Vector3(+1.0f, 0.0f, 0.0f);
	}
	
	// SPACE キー or A ボタン
	if (Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
		Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_A))
	{
		Jump();
	}

	BaseCharacter::Update();

	// 着地しているなら
	if (MapChipCollider::CollisionBit() & ChipCollisionBit::kBottom)
	{
		// ジャンプ回数初期化
		jumpCounter_ = 0;

		// 瞬間
		if ((MapChipCollider::CollisionBit() & ChipCollisionBit::kElderBottom) == 0)
		{
			// 着地アニメーション
			drawer_->PlayAnimation(
				static_cast<uint16_t>(PlayerDrawer::AnimationType::eLanding), 
				PlayerAnimationConfig::Landing::kFrame
			);

			// 移動アニメーション
			drawer_->PlayAnimation(
				static_cast<uint16_t>(PlayerDrawer::AnimationType::eMove),
				PlayerAnimationConfig::Move::kFrame,
				true
			);
		}
	}
	// 離陸した瞬間
	else if(MapChipCollider::CollisionBit() & ChipCollisionBit::kElderBottom)
	{
		// 移動アニメーションをやめる
		drawer_->AbortAnimation(static_cast<uint16_t>(PlayerDrawer::AnimationType::eMove));
	}

	// V キー or X ボタン
	if (Keys::GetInstance()->IsTrigger(DIK_V) ||
		Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_X))
	{
		Attack();
	}
}

void Player::OnCollision(const CollisionInfo& info)
{
	// 敵
	if (info.attribute_  == AttributeType::eEnemy)
	{
		// 自分 が 敵 より上にいる なら
		if (transform_->pos_.y_ - (PlayerConfig::kRadius / 2.0f) >= info.pos_.y_ + (info.radius_ / 2.0f))
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
			// ダメージを受ける
			status_.Damage(info.pStatus_->Attack(), true);

			if (status_.IsAlive() == false)
			{
				// 攻撃アニメーション
				drawer_->PlayAnimation(
					static_cast<uint16_t>(PlayerDrawer::AnimationType::eDead),
					PlayerAnimationConfig::kDeadFrame
				);

				spScrollCamera_->SetFollowPoint(nullptr);
				YGame::SceneExecutive::GetInstance()->Change("PLAY", "BLACKOUT", 10, 5);
			}

			spScrollCamera_->Shaking(2.0f, 0.2f, 100.0f);

			// 被弾アニメーション
			drawer_->PlayAnimation(
				static_cast<uint16_t>(PlayerDrawer::AnimationType::eHit), 
				PlayerAnimationConfig::Hit::kFrame
			);
		}

		return;
	}

	// ペット
	if (info.attribute_ == AttributeType::ePet)
	{
		// 乗る
		RideOnPet(static_cast<IPet*>(info.pSelf_));

		return;
	}
}

YGame::BaseCharacter::CollisionInfo Player::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute_ = collider_->Attribute();
	result.pos_ = transform_->pos_;
	result.radius_ = PlayerConfig::kRadius;
	result.pStatus_ = &status_;
	result.pSelf_ = this;

	return result;
}

void Player::Jump(const bool isJumpCount)
{
	// ペットいるなら
	if (pPet_)
	{
		// ペットでジャンプ
		pPet_->Jump();

		return;
	}

	// ジャンプカウントするなら
	if (isJumpCount)
	{
		// ジャンプ回数 が 最大回数超えてたら 弾く
		if (jumpCounter_ >= maxJumpCount_) { return; }

		jumpCounter_++;
	}

	speed_.VelocityRef().y_ = 0.0f;

	moveDirection_.y_ = 1.0f;

	// ジャンプアニメーション
	drawer_->PlayAnimation(
		static_cast<uint16_t>(PlayerDrawer::AnimationType::eJump), 
		PlayerAnimationConfig::Jump::kFrame
	);
}

void Player::Attack()
{
	// ペットいるなら
	if (pPet_)
	{
		// ペットで攻撃
		pPet_->Attack();
		
		return;
	}

	// 攻撃新規生成
	SlashAttack* newAttack = new SlashAttack();

	newAttack->Initialize(
		SlashAttackConfig::kAliveTime,
		&transform_->pos_,
		SlashAttackConfig::kOffset, 
		SlashAttackConfig::kRadius, 
		SlashAttackConfig::kPower);
	
	CharacterManager::GetInstance()->PushBack(newAttack);

	// 攻撃アニメーション
	drawer_->PlayAnimation(
		static_cast<uint16_t>(PlayerDrawer::AnimationType::eAttack), 
		PlayerAnimationConfig::kAttackFrame
	);
}

void Player::OffScreenProcess()
{
	if (YGame::TransitionManager::GetInstance()->IsAct()) { return; }

	YGame::SceneExecutive::GetInstance()->Change("PLAY", "BLACKOUT", 10, 5);
}

void Player::DrawDebugTextContent()
{
	BaseCharacter::DrawDebugTextContent();
}

void Player::StaticInitialize(ScrollCamera* pScrollCamera)
{
	assert(pScrollCamera);
	
	spScrollCamera_ = pScrollCamera;
}
