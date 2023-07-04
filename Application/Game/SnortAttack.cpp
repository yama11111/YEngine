#include "SnortAttack.h"
#include "SphereCollider.h"
#include "SnortAttackDrawer.h"

#include "CharacterConfig.h"

using YGame::SnortAttack;
using YMath::Vector3;


void SnortAttack::Initialize(
	const uint32_t aliveTimer, 
	const Vector3& emitPos, 
	const Vector3& acceleration, 
	const Vector3& maxSpeed, 
	const float radius, 
	const uint32_t attackPower)
{
	// �Q�[���L�����N�^�[������
	ICharacter::Initialize(
		"SnortAttack",
		Transform::Status::Default(),
		acceleration, maxSpeed,
		1, attackPower, 0,
		new SphereCollider({}, AttributeType::ePlayer, AttributeType::eEnemy, radius),
		new SnortAttackDrawer(DrawLocation::eCenter));

	transform_->scale_ = Vector3(radius, radius, radius);

	// ���˕Ԃ�Ȃ�
	MapChipCollider::SetIsBounce(false);

	// �������ԏ����� + �X�^�[�g
	aliveTimer_.Initialize(aliveTimer);
	aliveTimer_.SetActive(true);

	transform_->pos_ = emitPos;

	// �I�u�W�F�N�g�X�V
	GameObject::Update();
}

void SnortAttack::Update()
{
	moveDirection_ = Vector3(+1.0f, 0.0f, 0.0f);

	// �L�����N�^�[�X�V
	ICharacter::Update();

	aliveTimer_.Update();

	if (aliveTimer_.IsEnd())
	{
		// ����
		status_.SetHP(0);
	}
}

void SnortAttack::OnCollision(const CollisionInfo& info)
{
	// �G
	if (info.attribute_ == AttributeType::eEnemy)
	{
		// �_���[�W��^����
		info.pStatus_->Damage(status_.Attack(), true);
	}
}

YGame::ICharacter::CollisionInfo SnortAttack::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute_ = collider_->Attribute();
	result.pos_ = transform_->pos_;
	result.radius_ = transform_->scale_.x_;
	result.pStatus_ = &status_;
	result.pSelf_ = this;

	return result;
}

void SnortAttack::DrawDebugTextContent()
{
	ICharacter::DrawDebugTextContent();
}
