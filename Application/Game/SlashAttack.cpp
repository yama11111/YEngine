#include "SlashAttack.h"
#include "SphereCollider.h"
#include "SlashAttackDrawer.h"

#include "CharacterConfig.h"

using YGame::SlashAttack;
using YMath::Vector3;

void SlashAttack::Initialize(const Transform::Status& status, const uint32_t aliveTimer, const uint32_t attackPower)
{
	// �Q�[���L�����N�^�[������
	ICharacter::Initialize(
		"SlashAttack",
		status,
		Vector3(), Vector3(),
		1, attackPower, 0,
		new SphereCollider({}, AttributeType::ePlayer, AttributeType::eEnemy, status.scale_.x_),
		new SlashAttackDrawer(DrawLocation::eCenter));

	// ���˕Ԃ�Ȃ�
	MapChipCollider::SetIsBounce(false);

	// �������ԏ����� + �X�^�[�g
	aliveTimer_.Initialize(aliveTimer);
	aliveTimer_.SetActive(true);
}

void SlashAttack::Update()
{
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

void SlashAttack::DrawDebugTextContent()
{
	ICharacter::DrawDebugTextContent();
}
