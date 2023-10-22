#include "IEnemy.h"
#include "CharacterConfig.h"

using YGame::IEnemy;

void IEnemy::OnCollision(const CollisionInfo& info)
{
	// 自身の情報
	CollisionInfo self = GetCollisionInfo();
	
		// プレイヤー or ペット
	if (info.attribute == AttributeType::ePlayer || 
		info.attribute == AttributeType::ePet)
	{
		// 自分 が 下側 なら
		if (self.pos.y_ + (self.radius / 2.0f) < info.pos.y_ - (info.radius / 2.0f))
		{
			// 被弾
			Hit();
		}

		return;
	}
}

void IEnemy::Hit()
{
	//// ダメージを受ける
	//status_.Damage(info.pStatus->Attack(), true);

	//spScrollCamera_->Shaking(4.0f, 2.0f, 100.0f);
}
