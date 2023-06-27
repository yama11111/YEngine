#include "IEnemy.h"

using YGame::IEnemy;

void IEnemy::Update()
{
	// キャラクター更新
	ICharacter::Update();
}

void IEnemy::Draw()
{
	// 描画
	drawer_->Draw();
}

void IEnemy::OnCollision(const CollisionInfo& info)
{

}
