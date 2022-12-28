#include "Enemy.h"
#include "CharaConfig.h"
#include "CollisionConfig.h"
#include <cassert>

void Enemy::OnCollision(const uint32_t attribute, const YMath::Vec3& pos)
{
	if (attribute == Collision::Attribute::Player)
	{
		// “¥‚Ü‚ê‚½‚È‚ç
		if (pos.y_ - obj_.pos_.y_ >= CharaConfig::AttackRange)
		{
			Hit(1);
		}
	}
}
