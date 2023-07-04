#include "SlashAttack.h"
#include "SphereCollider.h"
#include "SlashAttackDrawer.h"

#include "CharacterConfig.h"

using YGame::SlashAttack;
using YMath::Vector3;

void SlashAttack::Initialize(
	const uint32_t aliveTimer, 
	Vector3* pAttackerPos, 
	const Vector3& offset, 
	const float radius, 
	const uint32_t attackPower)
{
	// �Q�[���L�����N�^�[������
	ICharacter::Initialize(
		"SlashAttack",
		Transform::Status::Default(),
		Vector3(), Vector3(),
		1, attackPower, 0,
		new SphereCollider({}, AttributeType::ePlayer, AttributeType::eEnemy, radius),
		new SlashAttackDrawer(DrawLocation::eCenter));

	transform_->scale_ = Vector3(radius, radius, radius);

	// ���˕Ԃ�Ȃ�
	MapChipCollider::SetIsBounce(false);

	// �������ԏ����� + �X�^�[�g
	aliveTimer_.Initialize(aliveTimer);
	aliveTimer_.SetActive(true);

	pAttackerPos_ = pAttackerPos;

	offset_ = offset;

	UpdatePos();
	
	// �I�u�W�F�N�g�X�V
	GameObject::Update();
}

void SlashAttack::Update()
{
	UpdatePos();

	// �L�����N�^�[�X�V
	ICharacter::Update();

	aliveTimer_.Update();
	
	if (aliveTimer_.IsEnd())
	{
		// ����
		status_.SetHP(0);
	}
}

void SlashAttack::OnCollision(const CollisionInfo& info)
{
	// �G
	if (info.attribute_ == AttributeType::eEnemy)
	{
		// �_���[�W��^����
		info.pStatus_->Damage(status_.Attack(), true);
	}
}

YGame::ICharacter::CollisionInfo SlashAttack::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute_ = collider_->Attribute();
	result.pos_ = transform_->pos_;
	result.radius_ = transform_->scale_.x_;
	result.pStatus_ = &status_;
	result.pSelf_ = this;

	return result;
}

void SlashAttack::UpdatePos()
{
	transform_->pos_ = *pAttackerPos_ + offset_;
}

void SlashAttack::DrawDebugTextContent()
{
	ICharacter::DrawDebugTextContent();
}
