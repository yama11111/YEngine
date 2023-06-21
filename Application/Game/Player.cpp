#include "Player.h"
#include "PlayerDrawer.h"
#include "CollisionConfig.h"
#include "Keys.h"
#include "Pad.h"
#include <cassert>

using YGame::Player;
using YMath::Vector3;
using YInput::Keys;
using YInput::Pad;

YGame::ScrollCamera* Player::spScrollCamera_ = nullptr;

static const float Radius = 1.0f;
static const Vector3 Acceleration = { 0.1f,1.0f,0.0f };
static const Vector3 MaxSpeed = { 0.3f,1.0f,0.0f };
static const uint16_t MaxJumpCount = 2;
static const uint32_t HP = 3;
static const uint32_t Attack = 20;
static const uint32_t InvincibleTime = 10;

void Player::Initialize(const Transform::Status& status, IPet* pPet)
{
	// ゲームキャラクター初期化
	IGameCharacter::Initialize(
		Attribute::Player, Attribute::All, 
		status,
		Radius, 
		Acceleration, MaxSpeed,
		HP, Attack, InvincibleTime,
		new PlayerDrawer(), DrawLocation::eCenter);

	// ジャンプカウンター初期化
	jumpCounter_ = 0;

	// 最大ジャンプ回数初期化
	maxJumpCount_ = MaxJumpCount;

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
	IGameCharacter::Update();

	// 着地しているなら
	if (MapChipCollider::IsLanding())
	{
		// ジャンプ回数初期化
		jumpCounter_ = 0;
	}
}

void Player::Jump()
{
	// ジャンプ回数 が 最大回数超えてたら 弾く
	if (jumpCounter_ >= maxJumpCount_) { return; }

	// y軸 に進む
	moveDirection_.y_ = 1.0f;

	// ジャンプカウント
	jumpCounter_++;
}

void Player::Draw()
{
	// 描画
	drawer_->Draw(DrawLocation::eCenter);
}

void Player::OnCollision(IGameCharacter* pPair)
{
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
