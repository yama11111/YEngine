#include "NeedleAttack.h"
#include "NeedleAttackDrawer.h"
#include "CharacterConfig.h"

#include "CollisionDrawer.h"
#include "Box2DCollider.h"

using YGame::NeedleAttack;
using YMath::Vector2;
using YMath::Vector3;
using YMath::BitFrag;

std::unique_ptr<NeedleAttack> NeedleAttack::Create(
	const uint32_t aliveTimer, 
	const Vector3& emitPos, 
	const Vector3& acceleration, 
	const Vector3& maxSpeed, 
	const float radius, 
	const uint32_t attackPower)
{
	std::unique_ptr<NeedleAttack> newObj = std::make_unique<NeedleAttack>();

	newObj->Initialize(
		aliveTimer,
		emitPos,
		acceleration,
		maxSpeed,
		radius,
		attackPower);

	return std::move(newObj);
}

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
		"NeedleAttack",
		Transform::Status::Default(),
		{ +1.0f, 0.0f, 0.0f }, // 右向き
		acceleration, maxSpeed, false,
		1, attackPower, 0);

	BitFrag attribute{};
	attribute.SetFragTrue(AttributeType::ePlayerAttack);

	SetCollider(GameCollider::Create(attribute));

	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::eEnemy);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&transform_->pos_, speed_.VelocityPtr(), Vector2(radius, radius), Vector3(), false, false),
			mask);
	}

	SetDrawer(NeedleAttackDrawer::Create(nullptr, 3));

	transform_->scale_ = Vector3(radius, radius, radius);
	transform_->Initialize();

	//InsertSubDrawer(CollisionDrawer::Name(), CollisionDrawer::Create(transform_.get(), radius, 1));

	// 生存時間初期化 + スタート
	aliveTimer_.Initialize(aliveTimer);
	aliveTimer_.SetActive(true);

	drawer_->PlayAnimation(static_cast<uint16_t>(NeedleAttackDrawer::AnimationType::eAttack), aliveTimer);

	transform_->pos_ = emitPos;

	// オブジェクト更新
	transform_->UpdateMatrix();
	drawer_->Update();
}

void NeedleAttack::UpdateBeforeCollision()
{
	moveDirection_ = Vector3(+1.0f, 0.0f, 0.0f);
	BaseCharacter::UpdateBeforeCollision();
}

void NeedleAttack::UpdateAfterCollision()
{
	BaseCharacter::UpdateAfterCollision();

	aliveTimer_.Update();

	if (aliveTimer_.IsEnd())
	{
		// 死ぬ
		status_.SetHP(0);
	}
}

void NeedleAttack::OnCollision(const InfoOnCollision& info)
{
	// 敵
	if (info.attribute == AttributeType::eEnemy)
	{
		// ダメージを与える
		//info.pStatus->Damage(status_.Attack(), true);
	}
}

YGame::InfoOnCollision NeedleAttack::GetInfoOnCollision()
{
	InfoOnCollision result = BaseCharacter::GetInfoOnCollision();

	result.attribute = AttributeType::ePlayerAttack;
	result.radius = transform_->scale_.x_;

	return result;
}

void NeedleAttack::DrawDebugTextContent()
{
	BaseCharacter::DrawDebugTextContent();
}
