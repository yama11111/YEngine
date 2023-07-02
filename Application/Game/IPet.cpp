#include "IPet.h"
#include "MapChipCollisionBitConfig.h"
#include "CharacterConfig.h"

#include "Keys.h"
#include "Pad.h"

#include <cassert>

using YGame::IPet;
using YInput::Keys;
using YInput::Pad;

YGame::ScrollCamera* IPet::spScrollCamera_ = nullptr;

void IPet::Update()
{

	// �����őO�ɐi��
	moveDirection_.x_ = +1.0f;

	ICharacter::Update();

	// ���n���Ă���Ȃ�
	if (MapChipCollider::CollisionBit() & ChipCollisionBit::kBottom)
	{
		// �W�����v�񐔏�����
		jumpCounter_ = 0;
	}
}

void IPet::OnCollision(const CollisionInfo& info)
{
	// �G
	if (info.attribute_ == AttributeType::eEnemy)
	{
		// ���� �� �G ����ɂ��� �Ȃ�
		if (transform_->pos_.y_ - (PetConfig::kRadius / 2.0f) >= info.pos_.y_ + (info.radius_ / 2.0f))
		{
			// �_���[�W��^����
			info.pStatus_->Damage(status_.Attack(), true);

			// �W�����v
			Jump(false);
		}
		// ���� �� �G ��艺 �Ȃ�
		else
		{
			isHit_ = true;
		}

		return;
	}
}

void IPet::Rideen()
{
	isRidden_ = true;
	
	isHit_ = false;

	spScrollCamera_->SetFollowPoint(&transform_->pos_);

	speed_.SetAcceleration(PetConfig::kNormalAcceleration);
	speed_.SetMax(PetConfig::kNormalMaxSpeed);
}

void IPet::GotOff()
{
	isRidden_ = false;

	speed_.SetAcceleration(PetConfig::kRunAcceleration);
	speed_.SetMax(PetConfig::kRunMaxSpeed);
}

void IPet::StaticInitialize(ScrollCamera* pScrollCamera)
{
	assert(pScrollCamera);

	spScrollCamera_ = pScrollCamera;
}

void IPet::Jump(const bool isJumpCount)
{
	// �W�����v�J�E���g����Ȃ�
	if (isJumpCount)
	{
		// �W�����v�� �� �ő�񐔒����Ă��� �e��
		if (jumpCounter_ >= maxJumpCount_) { return; }

		jumpCounter_++;
	}

	speed_.VelocityRef().y_ = 0.0f;

	moveDirection_.y_ = 1.0f;
}
