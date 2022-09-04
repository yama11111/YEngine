#include "Enemy.h"
#include "SphereBullet.h"
#include "SlashBullet.h"
#include "ScrewBullet.h"
#include "Player.h"
#include "Math/Calc.h"
#include <cassert>

void Enemy::FollowEyes()
{
	Vec3 v = player->GetWorldPos();
	v -= obj.mW.pos;
	v.Normalized();
	obj.mW.rota = AdjustAngle(v);
}

void Enemy::SetTarget()
{
	if (CollRaySphere(player->scope->ray->start, player->scope->ray->velocity, obj.mW.pos, seekRad))
	{
		if (player->scope->cursor->target)
		{
			Vec3 dist1 = player->target; // ‘O
			dist1 -= player->GetWorldPos();

			Vec3 dist2 = obj.mW.pos; // ¡
			dist2 -= player->GetWorldPos();

			if (dist1.Length() <= dist2.Length()) return;	
		}
		player->target = obj.mW.pos;
		player->scope->cursor->target = true;
	}
}

Vec3 Enemy::GetWorldPos() 
{
	Vec3 pos = obj.mW.pos;
	return pos;
}

void Enemy::OnCollision(const int damage)
{
	if (!status.isDeath)
	{
		status.Damage(damage);
		status.isHit = true;
		if (status.isDeath) shake.Shaking(2.0, 0.3);
		else shake.Shaking(0.5, 0.1);
	}
}

void Enemy::HitAnimation()
{
	if (status.isHit)
	{
		obj.mW.pos += shake.GetValue();
		obj.cbM.Color(GetColor({ 255, 0, 255, 255 }));
		status.isHit = shake.GetValue().IsZero();
	}
	else
	{
		obj.cbM.Color({ 1,1,1,1 });
	}
}

void Enemy::DeathAnimation()
{
	if (status.isDeath)
	{
		obj.mW.pos += shake.GetValue();
		obj.cbM.Color({ 1,1,1,shake.Ratio()});
		isDead = shake.GetValue().IsZero();
	}
}

Object3D Enemy::GetObjD()
{
	Object3D result = obj;
	result.mW.pos += shake.GetValue();
	result.Update();
	return result;
}
