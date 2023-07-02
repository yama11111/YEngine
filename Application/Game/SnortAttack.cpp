#include "SnortAttack.h"
#include "SphereCollider.h"
#include "SnortAttackDrawer.h"

#include "CharacterConfig.h"

using YGame::SnortAttack;
using YMath::Vector3;

void SnortAttack::Initialize(const Transform::Status& status, const uint32_t aliveTimer, const uint32_t attackPower)
{
	// ゲームキャラクター初期化
	ICharacter::Initialize(
		"SnortAttack",
		status,
		Vector3(), Vector3(),
		1, attackPower, 0,
		new SphereCollider({}, AttributeType::ePlayer, AttributeType::eEnemy, status.scale_.x_),
		new SnortAttackDrawer(DrawLocation::eCenter));

	// 生存時間初期化 + スタート
	aliveTimer_.Initialize(aliveTimer);
	aliveTimer_.SetActive(true);
}

void SnortAttack::Update()
{
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
