#include "Player.h"
#include "PlayerDrawer.h"
#include "SphereCollider.h"
#include "MapChipCollisionBitConfig.h"
#include "Keys.h"
#include "Pad.h"
#include <cassert>
#include <imgui.h>

using YGame::Player;
using YMath::Vector3;
using YInput::Keys;
using YInput::Pad;

YGame::ScrollCamera* Player::spScrollCamera_ = nullptr;

static const float kRadius = 1.0f;
static const Vector3 kAcceleration = { 0.1f,1.0f,0.0f };
static const Vector3 kMaxSpeed = { 0.3f,1.0f,0.0f };
static const uint16_t kMaxJumpCount = 2;
static const uint32_t kHP = 3;
static const uint32_t kAttack = 20;
static const uint32_t kInvincibleTime = 10;

void Player::Initialize(const Transform::Status& status, IPet* pPet)
{
	// ゲームキャラクター初期化
	ICharacter::Initialize(
		"Player",
		status,
		kAcceleration, kMaxSpeed,
		kHP, kAttack, kInvincibleTime,
		new SphereCollider({}, AttributeType::ePlayer, AttributeType::eAll, kRadius),
		new PlayerDrawer(DrawLocation::eCenter));

	// ジャンプカウンター初期化
	jumpCounter_ = 0;

	// 最大ジャンプ回数初期化
	maxJumpCount_ = kMaxJumpCount;

	// 開始時は武装する
	isArmed_ = true;

	// ペット設定
	pPet_ = pPet;

	// スクロールカメラ追従点設定
	spScrollCamera_->SetFollowPoint(&transform_->pos_);
}

void Player::Update()
{
	// 自動で前に進む
	moveDirection_.x_ = +1.0f;

	// SPACE キー or A ボタン
	if (Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
		Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_A))
	{
		// ジャンプ
		Jump();
	}
	
	// キャラクター更新
	ICharacter::Update();

	// 着地しているなら
	if (MapChipCollider::CollisionBit() & ChipCollisionBit::kBottom)
	{
		// ジャンプ回数初期化
		jumpCounter_ = 0;
	}
}

void Player::OnCollision(const CollisionInfo& info)
{
	// 敵
	if (info.attribute_  == AttributeType::eEnemy)
	{
		// 自分 が 敵 より上にいる なら
		if (transform_->pos_.y_ - kRadius >= info.pos_.y_ + (info.radius_ / 2.0f))
		{
			// ダメージを与える
			info.pStatus_->Damage(status_.Attack(), true);

			// ジャンプ
			Jump(false);
		}
		// それ以外は (自分 が 敵 より下)
		else
		{
			// ダメージを受ける
			status_.Damage(info.pStatus_->Attack(), true);
		}
	}
}

YGame::ICharacter::CollisionInfo Player::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute_ = collider_->Attribute();
	result.pos_ = transform_->pos_;
	result.radius_ = kRadius;
	result.pStatus_ = &status_;

	return result;
}

void Player::Jump(const bool isJumpCount)
{
	// ジャンプカウントする
	if (isJumpCount)
	{
		// ジャンプ回数 が 最大回数超えてたら 弾く
		if (jumpCounter_ >= maxJumpCount_) { return; }

		jumpCounter_++;
	}

	// y軸 に進む
	moveDirection_.y_ = 1.0f;
}

void Player::DrawDebugTextContent()
{
	ICharacter::DrawDebugTextContent();
}

void Player::SetPetPointer(IPet* pPet)
{
	// nullチェック
	assert(pPet);

	// 代入
	pPet_ = pPet;
}

void Player::StaticInitialize(ScrollCamera* pScrollCamera)
{
	// nullチェック
	assert(pScrollCamera);

	// 代入
	spScrollCamera_ = pScrollCamera;
}
