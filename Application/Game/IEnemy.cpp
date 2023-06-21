#include "IEnemy.h"

using YGame::IEnemy;

void IEnemy::Update()
{
	// キャラクター更新
	IGameCharacter::Update();
}

void IEnemy::Draw()
{
	// 描画
	drawer_->Draw(DrawLocation::eCenter);
}

void IEnemy::OnCollision(IGameCharacter* pPair)
{

}
