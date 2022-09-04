#include "EnemyBullet.h"
#include "Math/Calc.h"
#include <cmath>
#include "Player.h"

void EnemyBullet::Initialize(const Vec3& pos, const Vec3& velocity, Model* model, const UINT tex)
{
}

void EnemyBullet::Initialize2(const Vec3& pos, const Vec3& velocity, 
	const float radius, const float radian, Model* model, const UINT tex)
{
}

void EnemyBullet::Homing() 
{
	homT.Update();
	if (homT.IsEnd())
	{
		isStraight = true;
	}
	if (!isStraight)
	{
		Vec3 fromVel = velocity;
		fromVel = fromVel.Normalized();

		Vec3 toPlayer = player->GetWorldPos() - obj.mW.pos;
		toPlayer.Normalized();

		velocity = Lerp(fromVel, toPlayer, inductive);
		velocity = velocity.Normalized();
		obj.mW.rota = AdjustAngle(velocity);
		velocity *= speed;
	}
}

Vec3 EnemyBullet::GetWorldPos()
{
	Vec3 pos = obj.mW.pos;
	return pos;
}

void EnemyBullet::OnCollision(const int damange) { isDead = true; }