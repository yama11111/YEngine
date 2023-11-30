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

void IEnemy::OnCollision(const InfoOnCollision& info)
{
	if (status_.IsInvincible()) { return; }

	// 自身の情報
	InfoOnCollision self = GetInfoOnCollision();
	
	// プレイヤー or ペット
	if (info.attribute == AttributeType::ePlayer || 
		info.attribute == AttributeType::ePet)
	{
		// 自分 が 下側 なら
		if (self.pTrfm->pos_.y_ + (self.radius / 4.0f) < info.pTrfm->pos_.y_ - (info.radius / 4.0f))
		{
			// ダメージを受ける
			status_.Damage(info.pStatus->Attack(), true);

			// 被弾
			Hit(info.pStatus->Attack(), true);
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
		Hit(info.pStatus->Attack(), false);
	}
}
