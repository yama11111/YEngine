#include "Player.h"
#include "PlayerDrawer.h"
#include "Keys.h"
#include "Pad.h"
#include <cassert>

using YGame::Player;
using YMath::Vector3;
using YInput::Keys;
using YInput::Pad;

static const float Radius = 0.0f;
static const Vector3 ScaleSize = { 1.0f,1.0f,1.0f };
static const Vector3 Acceleration = { 0.3f,1.5f,0.0f };
static const Vector3 MaxSpeed = { 1.5f,1.5f,0.0f };
static const uint16_t MaxJumpCount = 2;
static const uint32_t HP = 3;
static const uint32_t Attack = 20;

void Player::Initialize(const Vector3& pos, IPet* pPet)
{
	// �Q�[���L�����N�^�[������
	IGameCharacter::Initialize(
		GameObjectCollider::Type::ePlayer,
		{ pos, {}, ScaleSize },
		Radius, 
		Acceleration, MaxSpeed,
		MaxJumpCount,
		HP, Attack,
		new PlayerDrawer());

	// �J�n���͕�������
	isArmed_ = true;

	// �y�b�g�ݒ�
	pPet_ = pPet;
}

void Player::Update()
{
	// �����őO�ɐi��
	moveDirection_.x_ = 1.0f;

	// SPACE �L�[ or A �{�^��
	if (Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
		Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_A))
	{
		// �W�����v
		Jump();
	}
	
	// �L�����N�^�[�X�V
	IGameCharacter::Update();

	// �I�u�W�F�N�g�X�V
	IGameObject::Update();
}

void Player::Draw()
{
	// �`��
	drawer_->Draw(DrawLocation::eCenter);
}

void Player::SetPetPointer(IPet* pPet)
{
	// null�`�F�b�N
	assert(pPet);

	// ���
	pPet_ = pPet;
}
