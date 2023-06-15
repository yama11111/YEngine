#include "IGameCharacter.h"
#include "MapChipManager.h"

using YGame::IGameCharacter;
using YMath::Vector3;

void IGameCharacter::Initialize(
	const Type type, 
	const Transform::Status& status, 
	const float radius, 
	const Vector3& acceleration, const Vector3& maxSpeed, 
	const uint16_t maxJumpCount, 
	const uint32_t hp, const uint32_t attack,
	IDrawer* drawer)
{
	// �I�u�W�F�N�g������
	IGameObject::Initialize(type, status, radius, false, drawer);

	// �}�b�v�`�b�v�R���C�_�[������
	MapChipCollider::Initialize(status.scale_);

	// �X�s�[�h������
	speed_.Initialize(acceleration, maxSpeed);

	// �ő�W�����v�񐔏�����
	maxJumpCount_ = maxJumpCount;

	// �L�����N�^�[�X�e�[�^�X������
	status_.Initialize(hp, attack);
}

void IGameCharacter::Update()
{
	// �X�s�[�h�X�V
	speed_.Update(moveDirection_);

	// �ړ�����������
	moveDirection_ = Vector3();

	// �}�b�v�`�b�v�Ƃ̃A�^������
	MapChipManager::GetInstance()->CurrentMapPointer()->PerfectPixelCollision(*this);

	// ���n���Ă���Ȃ�
	if (MapChipCollider::IsLanding())
	{
		// �W�����v�񐔏�����
		jumpCounter_ = 0;
	}

	transform_->pos_ += speed_.Velocity();

	// �I�u�W�F�N�g�X�V
	IGameObject::Update();
}

bool IGameCharacter::IsAlive() const
{
	return status_.IsAlive();
}

Vector3& IGameCharacter::PosRef()
{
	return transform_->pos_;
}

Vector3& IGameCharacter::SpeedRef()
{
	return speed_.VelocityRef();
}

void IGameCharacter::Jump()
{
	// �W�����v�� �� �ő�񐔒����Ă��� �e��
	if (jumpCounter_ >= maxJumpCount_) { return; }

	// y�� �ɐi��
	moveDirection_.y_ = 1.0f;

	// �W�����v�J�E���g
	jumpCounter_++;
}
