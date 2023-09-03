#include "Slime.h"
#include "SlimeDrawer.h"
#include "CharacterConfig.h"
#include "AnimationConfig.h"

#include "CollisionDrawer.h"
#include "PrimitiveCollider.h"
#include "MapChipCollisionBitConfig.h"

#include "Def.h"
#include <cassert>

using YGame::Slime;
using YMath::Vector3;

void Slime::Initialize(const Transform::Status& status)
{
	// �Q�[���L�����N�^�[������
	BaseCharacter::Initialize(
		"Slime",
		status,
		{ -1.0f, 0.0f, 0.0f }, // ������
		SlimeConfig::kAcceleration, SlimeConfig::kMaxSpeed,
		SlimeConfig::kHP, SlimeConfig::kAttack, SlimeConfig::kInvincibleTime,
		new GameCollider(transform_.get(), AttributeType::eEnemy, AttributeType::eAll),
		SlimeDrawer::Create(nullptr, 1));

	collider_->PushBack(new YMath::SphereCollider(Vector3(), SlimeConfig::kRadius));

	InsertSubDrawer(CollisionDrawer::Name(), CollisionDrawer::Create(transform_.get(), SlimeConfig::kRadius, 1));

	// �����A�j���[�V����
	drawer_->PlayAnimation(
		static_cast<uint16_t>(SlimeDrawer::AnimationType::eIdle),
		SlimeAnimationConfig::kIdleFrame
	);
}

void Slime::Update(const bool isUpdate)
{
	BaseCharacter::Update(isUpdate);
	
	// ���n�����u��
	if ((MapChipCollider::CollisionBit() & ChipCollisionBit::kBottom) &&
		(MapChipCollider::CollisionBit() & ChipCollisionBit::kElderBottom) == 0)
	{
		// ���n�A�j���[�V����
		drawer_->PlayAnimation(
			static_cast<uint16_t>(SlimeDrawer::AnimationType::eLanding),
			SlimeAnimationConfig::Landing::kFrame
		);
	}
}

YGame::BaseCharacter::CollisionInfo Slime::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute_ = collider_->Attribute();
	result.pos_ = transform_->pos_;
	result.radius_ = SlimeConfig::kRadius;
	result.pStatus_ = &status_;
	result.pSelf_ = this;

	return result;
}

void Slime::Hit()
{
	IEnemy::Hit();

	// ��e�A�j���[�V����
	drawer_->PlayAnimation(
		static_cast<uint16_t>(SlimeDrawer::AnimationType::eHit),
		SlimeAnimationConfig::Hit::kFrame
	);

	if (status_.IsAlive() == false)
	{
		// ���S�A�j���[�V����
		drawer_->PlayAnimation(
			static_cast<uint16_t>(SlimeDrawer::AnimationType::eDead),
			SlimeAnimationConfig::Dead::kFrame
		);
	}
}
