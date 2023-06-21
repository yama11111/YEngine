#include "IGameCharacter.h"
#include "MapChipManager.h"

using YGame::IGameCharacter;
using YMath::Vector3;

void IGameCharacter::Initialize(
	const uint32_t attribute, const uint32_t mask,
	const Transform::Status& status, 
	const float radius, 
	const Vector3& acceleration, const Vector3& maxSpeed, 
	const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime, 
	IDrawer* drawer, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	IGameObject::Initialize(status, drawer, location);

	// �R���C�_�[�X�V
	BaseCollider::Initialize(attribute, mask, &transform_->pos_, radius);

	// �}�b�v�`�b�v�R���C�_�[������
	MapChipCollider::Initialize(status.scale_);

	// �X�s�[�h������
	speed_.Initialize(acceleration, maxSpeed);

	// �L�����X�e�[�^�X������
	status_.Initialize(hp, attack, invincibleTime);
}

void IGameCharacter::Update()
{
	// �X�s�[�h�X�V
	speed_.Update(moveDirection_);

	// �ړ�����������
	moveDirection_ = Vector3();

	// �}�b�v�`�b�v�Ƃ̃A�^������
	MapChipManager::GetInstance()->CurrentMapPointer()->PerfectPixelCollision(*this);

	// �ʒu�ɃX�s�[�h���Z
	transform_->pos_ += speed_.Velocity();

	// �I�u�W�F�N�g�X�V
	IGameObject::Update();

	// �R���C�_�[�X�V
	BaseCollider::Update();

	// �L�����X�e�[�^�X�X�V
	status_.Update();
}

bool IGameCharacter::IsAlive() const
{
	return status_.IsAlive();
}

YGame::CharacterStatus IGameCharacter::Status() const
{
	return status_;
}

Vector3& IGameCharacter::PosRef()
{
	return transform_->pos_;
}

Vector3& IGameCharacter::SpeedRef()
{
	return speed_.VelocityRef();
}
