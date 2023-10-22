#include "Player.h"
#include "PlayerDrawer.h"
#include "CharacterConfig.h"
#include "CharacterManager.h"
#include "SlashAttack.h"

#include "PrimitiveCollider.h"
#include "MapChipCollisionBitConfig.h"
#include "CollisionDrawer.h"

#include "StageManager.h"

#include "Keys.h"
#include "Pad.h"

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

	transform_->Initialize();

	collider_->PushBack(new YMath::SphereCollider(Vector3(), PlayerConfig::kRadius));

	InsertSubDrawer(CollisionDrawer::Name(), CollisionDrawer::Create(transform_.get(), PlayerConfig::kRadius, 1));

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
	drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eIdle), true);
}

void Player::RideOnPet(IPet* pPet)
{
	pPet_ = pPet;

	if (pPet_)
	{
		// 親子関係
		SetParent(pPet_);

		// 乗る位置分 上に移動
		transform_->pos_ = pPet_->RidingPosHeight();
		transform_->UpdateMatrix();

		speed_.SetIsGravity(false);

		speed_.Reset();

		collider_->SetIsSlip(true);

		drawer_->SetParent(pPet_->DrawerPtr()->TransformPtr());
		drawer_->SetOffset(pPet_->RidingPosHeight());
		drawer_->SetIsVisibleUpdate(false);

		pPet_->Rideen();

		// 移動アニメーションをやめる
		drawer_->StopAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eMove));
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
	drawer_->SetOffset(Vector3(0.0f, 0.0f, 0.0f));
	drawer_->SetIsVisibleUpdate(true);
	
	// 飛び降りる
	Jump(false);

	// カメラを自分追従に
	spScrollCamera_->SetFollowPoint(&transform_->pos_);

	// 移動アニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eMove), true);
}

void Player::Update(const bool isUpdate)
{
	// ペットが被弾したら降りる
	if(pPet_)
	{
		if (pPet_->IsHit())
		{
			GetOffPet();
		}
	}
	
	if (isUpdate)
	{
		if (pPet_ == nullptr)
		{
			// 自動で前に進む
			moveDirection_ += Vector3(+1.0f, 0.0f, 0.0f);
			direction_ = Vector3(+1.0f, 0.0f, 0.0f);
		}
		else
		{
			direction_ = Vector3(-1.0f, 0.0f, 0.0f);
		}

		// SPACE キー or A ボタン
		if (Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
			Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_A))
		{
			Jump();
		}

		// V キー or X ボタン
		if (Keys::GetInstance()->IsTrigger(DIK_V) ||
			Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_X))
		{
			Attack();
		}
	}

	BaseCharacter::Update(isUpdate);

	// 着地しているなら
	if (MapChipCollider::CollisionBit() & ChipCollisionBit::kBottom)
	{
		// ジャンプ回数初期化
		jumpCounter_ = 0;

		// 瞬間
		if ((MapChipCollider::CollisionBit() & ChipCollisionBit::kElderBottom) == 0)
		{
			// 着地アニメーション
			drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eLanding), true);

			// 移動アニメーション
			drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eMove), false);
		}
	}
	// 離陸した瞬間
	else if(MapChipCollider::CollisionBit() & ChipCollisionBit::kElderBottom)
	{
		// 移動アニメーションをやめる
		drawer_->StopAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eMove));
	}
}

void Player::OnCollision(const CollisionInfo& info)
{
	// 敵
	if (info.attribute  == AttributeType::eEnemy)
	{
		// 自分 が 敵 より上にいる なら
		if (transform_->pos_.y_ - (PlayerConfig::kRadius / 2.0f) >= info.pos.y_ + (info.radius / 2.0f))
		{
			// ダメージを与える
			info.pStatus->Damage(status_.Attack(), true);

			spScrollCamera_->Shaking(1.0f, 0.2f, 100.0f);

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

				spScrollCamera_->SetFollowPoint(nullptr);
				StageManager::GetInstance()->GameOver();
			}

			spScrollCamera_->Shaking(2.0f, 0.2f, 100.0f);

			// 被弾アニメーション
			drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eHit), true);
		}

		return;
	}

	// ペット
	if (info.attribute == AttributeType::ePet)
	{
		// 乗る
		RideOnPet(static_cast<IPet*>(info.pSelf));

		return;
	}
}

YGame::BaseCharacter::CollisionInfo Player::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute = collider_->Attribute();
	result.pos		 = transform_->pos_;
	result.radius	 = PlayerConfig::kRadius;
	result.pStatus	 = &status_;
	result.pSelf	 = this;

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
	drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eJump), true);
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
		static_cast<uint32_t>(PlayerDrawer::AnimationType::eAttack), true);
}

void Player::OffScreenProcess()
{
	StageManager::GetInstance()->GameOver();
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
