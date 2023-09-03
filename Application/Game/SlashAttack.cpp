#include "SlashAttack.h"
#include "SlashAttackDrawer.h"
#include "CharacterConfig.h"

#include "CollisionDrawer.h"
#include "PrimitiveCollider.h"


using YGame::SlashAttack;
using YMath::Vector3;

void SlashAttack::Initialize(
	const uint32_t aliveTimer, 
	Vector3* pAttackerPos, 
	const Vector3& offset, 
	const float radius, 
	const uint32_t attackPower)
{
	// ゲームキャラクター初期化
	BaseCharacter::Initialize(
		"SlashAttack",
		Transform::Status::Default(),
		{ +1.0f, 0.0f, 0.0f }, // 右向き
		Vector3(), Vector3(),
		1, attackPower, 0,
		new GameCollider(transform_.get(), AttributeType::ePlayer, AttributeType::eEnemy),
		SlashAttackDrawer::Create(nullptr, 3));

	collider_->PushBack(new YMath::SphereCollider(Vector3(), radius));

	InsertSubDrawer(CollisionDrawer::Name(), CollisionDrawer::Create(transform_.get(), radius, 1));

	transform_->scale_ = Vector3(radius, radius, radius);

	// 跳ね返らない
	MapChipCollider::SetIsBounce(false);

	// 生存時間初期化 + スタート
	aliveTimer_.Initialize(aliveTimer);
	aliveTimer_.SetActive(true);

	drawer_->PlayAnimation(static_cast<uint16_t>(SlashAttackDrawer::AnimationType::eAttack), aliveTimer);

	pAttackerPos_ = pAttackerPos;

	offset_ = offset;

	UpdatePos();
	
	// オブジェクト更新
	GameObject::Update();
}

void SlashAttack::Update(const bool isUpdate)
{
	UpdatePos();

	// キャラクター更新
	BaseCharacter::Update(isUpdate);

	aliveTimer_.Update();
	
	if (aliveTimer_.IsEnd())
	{
		// 死ぬ
		status_.SetHP(0);
	}
}

void SlashAttack::OnCollision(const CollisionInfo& info)
{
	// 敵
	if (info.attribute_ == AttributeType::eEnemy)
	{
		// ダメージを与える
		info.pStatus_->Damage(status_.Attack(), true);
	}
}

YGame::BaseCharacter::CollisionInfo SlashAttack::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute_ = collider_->Attribute();
	result.pos_ = transform_->pos_;
	result.radius_ = transform_->scale_.x_;
	result.pStatus_ = &status_;
	result.pSelf_ = this;

	return result;
}

void SlashAttack::UpdatePos()
{
	transform_->pos_ = *pAttackerPos_ + offset_;
}

void SlashAttack::DrawDebugTextContent()
{
	BaseCharacter::DrawDebugTextContent();
}
