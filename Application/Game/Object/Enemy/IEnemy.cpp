#include "IEnemy.h"
#include "CharacterConfig.h"

using YGame::IEnemy;
using YMath::Vector3;

void IEnemy::UpdateBeforeCollision()
{
	blowTim_.Update();
	if (blowTim_.IsAct())
	{
		moveDirection_ += Vector3(+1.0f, +1.0f, 0.0f);
	}

	BaseCharacter::UpdateBeforeCollision();
}

void IEnemy::UpdateAfterCollision()
{
	BaseCharacter::UpdateAfterCollision();
}

void IEnemy::OnCollision(const ICollisionInfomation& info)
{
	if (status_.IsInvincible()) { return; }

	// 自身の情報
	ICollisionInfomation self = GetCollisionInfomation();
	
	// プレイヤー
	if (info.attribute == AttributeType::ePlayer)
	{
		// 自分 が 下側 なら
		if (worldPos_.y + (self.radius / 4.0f) < info.pWorldPos->y - (info.radius / 4.0f))
		{
			// ダメージを受ける
			status_.Damage(info.pStatus->Attack(), true);

			// 被弾
			Hit(info.pStatus->Attack());
		}
	}
	// 攻撃
	else if(info.attribute == AttributeType::ePlayerAttack)
	{
		// ぶっ飛ぶ
		blowTim_.Reset(true);

		// ダメージを受ける
		status_.Damage(info.pStatus->Attack(), true);

		// 被弾
		Hit(info.pStatus->Attack());
	}
	// ブロック
	else if (info.attribute == AttributeType::eBlock)
	{
		if (worldPos_.y <= info.pWorldPos->y) { return; }

		// 着地
		isLanding_ = true;
	}
}
