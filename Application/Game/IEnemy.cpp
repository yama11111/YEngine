#include "IEnemy.h"
#include "CharacterConfig.h"

using YGame::IEnemy;

void IEnemy::Update()
{
	// �L�����N�^�[�X�V
	ICharacter::Update();
}

void IEnemy::Draw()
{
	// �`��
	drawer_->Draw();
}

void IEnemy::OnCollision(const CollisionInfo& info)
{
	// ���g�̏��
	CollisionInfo self = GetCollisionInfo();
	
		// �v���C���[ or �y�b�g
	if (info.attribute_ == AttributeType::ePlayer || 
		info.attribute_ == AttributeType::ePet)
	{
		// ���� �� ���� �Ȃ�
		if (self.pos_.y_ + (self.radius_ / 2.0f) < info.pos_.y_ - (info.radius_ / 2.0f))
		{
			// ��e
			Hit();
		}

		return;
	}
}

void IEnemy::Hit()
{
	//// �_���[�W���󂯂�
	//status_.Damage(info.pStatus_->Attack(), true);

	//spScrollCamera_->Shaking(4.0f, 2.0f, 100.0f);
}
