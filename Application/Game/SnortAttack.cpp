#include "SnortAttack.h"
#include "SphereCollider.h"
#include "SnortAttackDrawer.h"

#include "CharacterConfig.h"

using YGame::SnortAttack;
using YMath::Vector3;


void SnortAttack::Initialize(
	const uint32_t aliveTimer, 
	const Vector3& emitPos, 
	const Vector3& acceleration, 
	const Vector3& maxSpeed, 
	const float radius, 
	const uint32_t attackPower)
{
	// ゲームキャラクター初期化
	ICharacter::Initialize(
		"SnortAttack",
		Transform::Status::Default(),
		acceleration, maxSpeed,
		1, attackPower, 0,
		new SphereCollider({}, AttributeType::ePlayer, AttributeType::eEnemy, radius),
		new SnortAttackDrawer(DrawLocation::eCenter));

	transform_->scale_ = Vector3(radius, radius, radius);

	// 跳ね返らない
	MapChipCollider::SetIsBounce(false);

	// 生存時間初期化 + スタート
	aliveTimer_.Initialize(aliveTimer);
	aliveTimer_.SetActive(true);

	transform_->pos_ = emitPos;

	// オブジェクト更新
	GameObject::Update();
}

void SnortAttack::Update()
{
	moveDirection_ = Vector3(+1.0f, 0.0f, 0.0f);

	// キャラクター更新
	ICharacter::Update();

	aliveTimer_.Update();

	if (aliveTimer_.IsEnd())
	{
		// 死ぬ
		status_.SetHP(0);
	}
}

void SnortAttack::OnCollision(const CollisionInfo& info)
{
	// 敵
	if (info.attribute_ == AttributeType::eEnemy)
	{
		// ダメージを与える
		info.pStatus_->Damage(status_.Attack(), true);
	}
}

YGame::ICharacter::CollisionInfo SnortAttack::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute_ = collider_->Attribute();
	result.pos_ = transform_->pos_;
	result.radius_ = transform_->scale_.x_;
	result.pStatus_ = &status_;
	result.pSelf_ = this;

	return result;
}

void SnortAttack::DrawDebugTextContent()
{
	ICharacter::DrawDebugTextContent();
}
