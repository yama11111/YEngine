#include "ICharacter.h"
#include "MapChipManager.h"
#include <imgui.h>

using YGame::ICharacter;
using YMath::Vector3;

void ICharacter::Initialize(
	const std::string& name,
	const Transform::Status& status,
	const Vector3& acceleration, const Vector3& maxSpeed,
	const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime,
	GameCollider* collider, BaseDrawer* drawer)
{
	// �I�u�W�F�N�g������
	GameObject::Initialize(name, status);

	// �R���C�_�[�ݒ�
	GameObject::SetCollider(collider);
	
	// �`��N���X�ݒ�
	GameObject::SetDrawer(drawer);

	// �}�b�v�`�b�v�R���C�_�[������
	MapChipCollider::Initialize(status.scale_);

	// �X�s�[�h������
	speed_.Initialize(acceleration, maxSpeed);

	// �L�����X�e�[�^�X������
	status_.Initialize(hp, attack, invincibleTime);
}

void ICharacter::Update()
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
	GameObject::Update();

	// �L�����X�e�[�^�X�X�V
	status_.Update();

	// 
	if (transform_->pos_.y_ <= -150.0f)
	{
		OffScreenProcess();
	}
}

void ICharacter::DrawDebugTextContent()
{
	status_.DrawDebugTextContent();

	GameObject::DrawDebugTextContent();
}

void ICharacter::OffScreenProcess()
{
	status_.Damage(1000, false);
}