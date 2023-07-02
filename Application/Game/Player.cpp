#include "Player.h"
#include "PlayerDrawer.h"
#include "SphereCollider.h"
#include "MapChipCollisionBitConfig.h"

#include "CharacterConfig.h"

#include "CharacterManager.h"
#include "SlashAttack.h"

#include "Keys.h"
#include "Pad.h"

#include <cassert>
#include <imgui.h>

using YGame::Player;
using YMath::Vector3;
using YInput::Keys;
using YInput::Pad;

YGame::ScrollCamera* Player::spScrollCamera_ = nullptr;

void Player::Initialize(const Transform::Status& status, IPet* pPet)
{
	// �Q�[���L�����N�^�[������
	ICharacter::Initialize(
		"Player",
		status,
		PlayerConfig::kAcceleration, PlayerConfig::kMaxSpeed,
		PlayerConfig::kHP, PlayerConfig::kAttack, PlayerConfig::kInvincibleTime,
		new SphereCollider({}, AttributeType::ePlayer, AttributeType::eAll, PlayerConfig::kRadius),
		new PlayerDrawer(DrawLocation::eCenter));

	// �W�����v�J�E���^�[������
	jumpCounter_ = 0;

	// �ő�W�����v�񐔏�����
	maxJumpCount_ = PlayerConfig::kMaxJumpCount;

	// �J�n���͕�������
	isArmed_ = true;

	// �y�b�g
	RideOnPet(pPet);

	if (pPet_ == nullptr)
	{
		spScrollCamera_->SetFollowPoint(&transform_->pos_);
	}
}

void Player::RideOnPet(IPet* pPet)
{
	pPet_ = pPet;

	if (pPet_)
	{
		// �e�q�֌W
		SetParent(pPet_);

		// ���ʒu�� ��Ɉړ�
		transform_->pos_ = Vector3(0.0f, pPet_->RidingPosHeight(), 0.0f);
		transform_->UpdateMatrix();

		speed_.SetIsGravity(false);

		speed_.Reset();

		collider_->SetIsSlip(true);

		pPet_->Rideen();
	}
}

void Player::GetOffPet()
{
	pPet_->GotOff();

	transform_->pos_ += pPet_->PosRef();
	transform_->UpdateMatrix();

	pPet_ = nullptr;
	
	SetParent(nullptr);
	
	speed_.SetIsGravity(true);

	collider_->SetIsSlip(false);
	
	// ��э~���
	Jump(false);

	// �J�����������Ǐ]��
	spScrollCamera_->SetFollowPoint(&transform_->pos_);
}

void Player::Update()
{
	// �y�b�g����e������~���
	if(pPet_)
	{
		if (pPet_->IsHit())
		{
			GetOffPet();
		}
	}

	if (pPet_ == nullptr)
	{
		// �����őO�ɐi��
		moveDirection_.x_ = +1.0f;
	}
	
	// SPACE �L�[ or A �{�^��
	if (Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
		Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_A))
	{
		// �W�����v
		Jump();
	}

	ICharacter::Update();

	// ���n���Ă���Ȃ�
	if (MapChipCollider::CollisionBit() & ChipCollisionBit::kBottom)
	{
		// �W�����v�񐔏�����
		jumpCounter_ = 0;
	}

	// V �L�[ or X �{�^��
	if (Keys::GetInstance()->IsTrigger(DIK_V) ||
		Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_X))
	{
		// �U��
		Attack();
	}
}

void Player::OnCollision(const CollisionInfo& info)
{
	// �G
	if (info.attribute_  == AttributeType::eEnemy)
	{
		// ���� �� �G ����ɂ��� �Ȃ�
		if (transform_->pos_.y_ - PlayerConfig::kRadius >= info.pos_.y_ + (info.radius_ / 2.0f))
		{
			// �_���[�W��^����
			info.pStatus_->Damage(status_.Attack(), true);

			// �W�����v
			Jump(false);
		}
		// ���� �� �G ��艺 �Ȃ�
		else
		{
			// �_���[�W���󂯂�
			status_.Damage(info.pStatus_->Attack(), true);

			if (status_.IsAlive() == false)
			{
				spScrollCamera_->SetFollowPoint(nullptr);
			}
		}

		return;
	}

	// �y�b�g
	if (info.attribute_ == AttributeType::ePet)
	{
		// ���
		RideOnPet(static_cast<IPet*>(info.pSelf_));

		return;
	}
}

YGame::ICharacter::CollisionInfo Player::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute_ = collider_->Attribute();
	result.pos_ = transform_->pos_;
	result.radius_ = PlayerConfig::kRadius;
	result.pStatus_ = &status_;
	result.pSelf_ = this;

	return result;
}

void Player::Jump(const bool isJumpCount)
{
	// �y�b�g����Ȃ�
	if (pPet_)
	{
		// �y�b�g�ŃW�����v
		pPet_->Jump();

		return;
	}

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

void Player::Attack()
{
	// �y�b�g����Ȃ�
	if (pPet_)
	{
		// �y�b�g�ōU��
		pPet_->Attack();
		
		return;
	}

	// �U���V�K����
	SlashAttack* newAttack = new SlashAttack();

	newAttack->Initialize(
		{ transform_->pos_, {}, {1.0f,1.0f,1.0f} },
		SlashAttackConfig::kAliveTime,
		SlashAttackConfig::kPower
	);
	
	CharacterManager::GetInstance()->PushBack(newAttack);
}

void Player::DrawDebugTextContent()
{
	ICharacter::DrawDebugTextContent();
}

void Player::StaticInitialize(ScrollCamera* pScrollCamera)
{
	assert(pScrollCamera);
	
	spScrollCamera_ = pScrollCamera;
}
