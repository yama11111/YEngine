#include "BaseCharacter.h"
#include "MathVector.h"
#include "MathUtil.h"
#include "CharacterConfig.h"
#include "MapChipManager.h"
#include <imgui.h>

using YGame::BaseCharacter;
using YMath::Vector3;

void BaseCharacter::Initialize(
	const std::string& name,
	const Transform::Status& status,
	const Vector3& direction,
	const Vector3& acceleration, const Vector3& maxSpeed,
	const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime,
	GameCollider* collider, BaseDrawer* drawer)
{
	GameObject::Initialize(name, status);

	direction_ = direction;

	speed_.Initialize(acceleration, maxSpeed);

	status_.Initialize(hp, attack, invincibleTime);

	GameObject::SetCollider(collider);
	
	GameObject::SetDrawer(drawer);

	// �}�b�v�`�b�v�Ƃ̃A�^������̓X�P�[�������̂܂܎g��
	MapChipCollider::Initialize(status.scale_);
}

void BaseCharacter::Update(const bool isUpdate)
{
	speed_.Update(moveDirection_);
	
	moveDirection_ = Vector3();

	// �}�b�v�`�b�v�Ƃ̃A�^������
	MapChipManager::GetInstance()->CurrentMapPointer()->PerfectPixelCollision(*this);

	transform_->pos_ += speed_.Velocity();

	// ��������
	transform_->rota_ = YMath::AdjustAngle(direction_);

	GameObject::Update();

	status_.Update();

	// ��ʊO�Ȃ玀��
	if (YMath::InRange(transform_->pos_, -YGame::kMaxWorldSize, YGame::kMaxWorldSize) == false)
	{
		OffScreenProcess();
	}
}

void BaseCharacter::DrawDebugTextContent()
{
	status_.DrawDebugTextContent();

	GameObject::DrawDebugTextContent();
}

void BaseCharacter::OffScreenProcess()
{
	status_.Damage(1000, false);
}
