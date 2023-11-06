#include "NeedleAttack.h"
#include "NeedleAttackDrawer.h"
#include "CharacterConfig.h"

#include "CollisionDrawer.h"
#include "PrimitiveCollider.h"

using YGame::NeedleAttack;
using YMath::Vector3;


void NeedleAttack::Initialize(
	const uint32_t aliveTimer,
	const Vector3& emitPos,
	const Vector3& acceleration,
	const Vector3& maxSpeed,
	const float radius,
	const uint32_t attackPower)
{
	// ゲームキャラクター初期化
	BaseCharacter::Initialize(
		"SnortAttack",
		Transform::Status::Default(),
		{ +1.0f, 0.0f, 0.0f }, // 右向き
		acceleration, maxSpeed,
		1, attackPower, 0,
		NeedleAttackDrawer::Create(nullptr, 3));

	transform_->scale_ = Vector3(radius, radius, radius);
	transform_->Initialize();

	{
		attribute_ = AttributeType::ePlayerAttack;

		collider_->PushBack(
			attribute_, AttributeType::eEnemy,
			new YMath::SphereCollider(&transform_->pos_, radius));
	}

	InsertSubDrawer(CollisionDrawer::Name(), CollisionDrawer::Create(transform_.get(), radius, 1));

	// 跳ね返らない
	MapChipCollider::SetIsBounce(false);

	// 生存時間初期化 + スタート
	aliveTimer_.Initialize(aliveTimer);
	aliveTimer_.SetActive(true);

	drawer_->PlayAnimation(static_cast<uint16_t>(NeedleAttackDrawer::AnimationType::eAttack), aliveTimer);

	transform_->pos_ = emitPos;

	// オブジェクト更新
	GameObject::Update();

}

void NeedleAttack::Update(const bool isUpdate)
{
	moveDirection_ = Vector3(+1.0f, 0.0f, 0.0f);

	// キャラクター更新
	BaseCharacter::Update(isUpdate);

	aliveTimer_.Update();

	if (aliveTimer_.IsEnd())
	{
		// 死ぬ
		status_.SetHP(0);
	}
}

void NeedleAttack::OnCollision(const CollisionInfo& info)
{
	// 敵
	if (info.attribute == AttributeType::eEnemy)
	{
		// ダメージを与える
		info.pStatus->Damage(status_.Attack(), true);
	}
}

YGame::BaseCharacter::CollisionInfo NeedleAttack::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute = attribute_;
	result.pos = transform_->pos_;
	result.radius = transform_->scale_.x_;
	result.pStatus = &status_;
	result.pSelf = this;

	return result;
}

void NeedleAttack::DrawDebugTextContent()
{
	BaseCharacter::DrawDebugTextContent();
}
