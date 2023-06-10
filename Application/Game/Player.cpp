#include "Player.h"
#include "PlayerDrawer.h"
#include "Keys.h"
#include "Pad.h"
#include <cassert>

using YGame::Player;
using YMath::Vector3;
using YInput::Keys;
using YInput::Pad;

static const float Radius = 0.0f;
static const Vector3 ScaleSize = { 1.0f,1.0f,1.0f };
static const Vector3 Acceleration = { 0.3f,1.5f,0.0f };
static const Vector3 MaxSpeed = { 1.5f,1.5f,0.0f };
static const uint16_t MaxJumpCount = 2;
static const uint32_t HP = 3;
static const uint32_t Attack = 20;

void Player::Initialize(const Vector3& pos, IPet* pPet)
{
	// ゲームキャラクター初期化
	IGameCharacter::Initialize(
		GameObjectCollider::Type::ePlayer,
		{ pos, {}, ScaleSize },
		Radius, 
		Acceleration, MaxSpeed,
		MaxJumpCount,
		HP, Attack,
		new PlayerDrawer());

	// 開始時は武装する
	isArmed_ = true;

	// ペット設定
	pPet_ = pPet;
}

void Player::Update()
{
	// 自動で前に進む
	moveDirection_.x_ = 1.0f;

	// SPACE キー or A ボタン
	if (Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
		Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_A))
	{
		// ジャンプ
		Jump();
	}
	
	// キャラクター更新
	IGameCharacter::Update();

	// オブジェクト更新
	IGameObject::Update();
}

void Player::Draw()
{
	// 描画
	drawer_->Draw(DrawLocation::eCenter);
}

void Player::SetPetPointer(IPet* pPet)
{
	// nullチェック
	assert(pPet);

	// 代入
	pPet_ = pPet;
}
