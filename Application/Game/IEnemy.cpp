#include "IEnemy.h"

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

}
