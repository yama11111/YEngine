#include "IEnemy.h"

using YGame::IEnemy;

void IEnemy::Update()
{
	// �L�����N�^�[�X�V
	IGameCharacter::Update();
}

void IEnemy::Draw()
{
	// �`��
	drawer_->Draw(DrawLocation::eCenter);
}

void IEnemy::OnCollision(IGameCharacter* pPair)
{

}
