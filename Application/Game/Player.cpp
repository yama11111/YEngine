#include "Player.h"
#include "PlayerDrawer.h"
#include "CollisionConfig.h"
#include "Keys.h"
#include "Pad.h"
#include <cassert>

using YGame::Player;
using YMath::Vector3;
using YInput::Keys;
using YInput::Pad;

YGame::ScrollCamera* Player::spScrollCamera_ = nullptr;

static const float Radius = 1.0f;
static const Vector3 Acceleration = { 0.1f,1.0f,0.0f };
static const Vector3 MaxSpeed = { 0.3f,1.0f,0.0f };
static const uint16_t MaxJumpCount = 2;
static const uint32_t HP = 3;
static const uint32_t Attack = 20;
static const uint32_t InvincibleTime = 10;

void Player::Initialize(const Transform::Status& status, IPet* pPet)
{
	// �Q�[���L�����N�^�[������
	IGameCharacter::Initialize(
		Attribute::Player, Attribute::All, 
		status,
		Radius, 
		Acceleration, MaxSpeed,
		HP, Attack, InvincibleTime,
		new PlayerDrawer(), DrawLocation::eCenter);

	// �W�����v�J�E���^�[������
	jumpCounter_ = 0;

	// �ő�W�����v�񐔏�����
	maxJumpCount_ = MaxJumpCount;

	// �J�n���͕�������
	isArmed_ = true;

	// �y�b�g�ݒ�
	pPet_ = pPet;

	// �X�N���[���J�����Ǐ]�_�ݒ�
	spScrollCamera_->SetFollowPoint(&transform_->pos_);
}

void Player::Update()
{
	// �����őO�ɐi��
	moveDirection_.x_ = +1.0f;

	// SPACE �L�[ or A �{�^��
	if (Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
		Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_A))
	{
		// �W�����v
		Jump();
	}
	
	// �L�����N�^�[�X�V
	IGameCharacter::Update();

	// ���n���Ă���Ȃ�
	if (MapChipCollider::IsLanding())
	{
		// �W�����v�񐔏�����
		jumpCounter_ = 0;
	}
}

void Player::Jump()
{
	// �W�����v�� �� �ő�񐔒����Ă��� �e��
	if (jumpCounter_ >= maxJumpCount_) { return; }

	// y�� �ɐi��
	moveDirection_.y_ = 1.0f;

	// �W�����v�J�E���g
	jumpCounter_++;
}

void Player::Draw()
{
	// �`��
	drawer_->Draw(DrawLocation::eCenter);
}

void Player::OnCollision(IGameCharacter* pPair)
{
}

void Player::SetPetPointer(IPet* pPet)
{
	// null�`�F�b�N
	assert(pPet);

	// ���
	pPet_ = pPet;
}

void Player::StaticInitialize(ScrollCamera* pScrollCamera)
{
	// null�`�F�b�N
	assert(pScrollCamera);

	// ���
	spScrollCamera_ = pScrollCamera;
}
