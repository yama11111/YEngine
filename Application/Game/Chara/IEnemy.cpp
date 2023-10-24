#include "IEnemy.h"
#include "CharacterConfig.h"

using YGame::IEnemy;
using YMath::Vector3;

void IEnemy::Update(const bool isUpdate)
{
	blowTim_.Update();
	if (blowTim_.IsAct())
	{
		moveDirection_ += Vector3(+1.0f, +1.0f, 0.0f);
	}

	BaseCharacter::Update(isUpdate);
}

void IEnemy::OnCollision(const CollisionInfo& info)
{
	if (status_.IsInvincible()) { return; }

	// 自身の情報
	CollisionInfo self = GetCollisionInfo();
	
	// プレイヤー or ペット
	if (info.attribute == AttributeType::ePlayer || 
		info.attribute == AttributeType::ePet)
	{
		// 自分 が 下側 なら
		if (self.pos.y_ + (self.radius / 2.0f) < info.pos.y_ - (info.radius / 2.0f))
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