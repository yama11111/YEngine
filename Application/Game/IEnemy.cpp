#include "IEnemy.h"
#include "CharacterConfig.h"

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
	// 自身の情報
	CollisionInfo self = GetCollisionInfo();
	
		// プレイヤー or ペット
	if (info.attribute_ == AttributeType::ePlayer || 
		info.attribute_ == AttributeType::ePet)
	{
		// 自分 が 下側 なら
		if (self.pos_.y_ + (self.radius_ / 2.0f) < info.pos_.y_ - (info.radius_ / 2.0f))
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
	//status_.Damage(info.pStatus_->Attack(), true);

	//spScrollCamera_->Shaking(4.0f, 2.0f, 100.0f);
}
