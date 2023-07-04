#include "Player.h"
#include "PlayerDrawer.h"
#include "SphereCollider.h"
#include "MapChipCollisionBitConfig.h"

#include "CharacterConfig.h"
#include "AnimationConfig.h"

#include "CharacterManager.h"
#include "SlashAttack.h"

#include "SceneExecutive.h"

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

	// �����A�j���[�V����
	drawer_->PlayAnimation(
		static_cast<uint16_t>(PlayerDrawer::AnimationType::eIdle), 
		PlayerAnimationConfig::kIdleFrame
	);
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

		drawer_->SetParent(pPet_->DrawerPtr()->TransformPtr());
		drawer_->SetIsVisibleUpdate(false);

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

	drawer_->SetParent(transform_.get());
	drawer_->SetIsVisibleUpdate(true);
	
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

		// �u��
		if ((MapChipCollider::CollisionBit() & ChipCollisionBit::kElderBottom) == 0)
		{
			// ���n�A�j���[�V����
			drawer_->PlayAnimation(
				static_cast<uint16_t>(PlayerDrawer::AnimationType::eLanding), 
				PlayerAnimationConfig::kLandingFrame
			);
		}
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
		if (transform_->pos_.y_ - (PlayerConfig::kRadius / 2.0f) >= info.pos_.y_ + (info.radius_ / 2.0f))
		{
			// �_���[�W��^����
			info.pStatus_->Damage(status_.Attack(), true);

			spScrollCamera_->Shaking(1.0f, 0.2f, 100.0f);

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
				// �U���A�j���[�V����
				drawer_->PlayAnimation(
					static_cast<uint16_t>(PlayerDrawer::AnimationType::eDead),
					PlayerAnimationConfig::kDeadFrame
				);

				spScrollCamera_->SetFollowPoint(nullptr);
				YScene::SceneExecutive::GetInstance()->Change("PLAY", "BLACKOUT", 10, 5);
			}

			spScrollCamera_->Shaking(2.0f, 0.2f, 100.0f);

			// ��e�A�j���[�V����
			drawer_->PlayAnimation(
				static_cast<uint16_t>(PlayerDrawer::AnimationType::eHit), 
				PlayerAnimationConfig::Hit::kFrame
			);
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

	// �W�����v�A�j���[�V����
	drawer_->PlayAnimation(
		static_cast<uint16_t>(PlayerDrawer::AnimationType::eJump), 
		PlayerAnimationConfig::kJumpFrame
	);
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
		SlashAttackConfig::kAliveTime,
		&transform_->pos_,
		SlashAttackConfig::kOffset, 
		SlashAttackConfig::kRadius, 
		SlashAttackConfig::kPower);
	
	CharacterManager::GetInstance()->PushBack(newAttack);

	// �U���A�j���[�V����
	drawer_->PlayAnimation(
		static_cast<uint16_t>(PlayerDrawer::AnimationType::eAttack), 
		PlayerAnimationConfig::kAttackFrame
	);
}

void Player::OffScreenProcess()
{
	if (YScene::TransitionManager::GetInstance()->IsAct()) { return; }

	YScene::SceneExecutive::GetInstance()->Change("PLAY", "BLACKOUT", 10, 5);
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
