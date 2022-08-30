#include "EnemyBullet.h"
#include "Calc.h"
#include <cmath>
#include "Player.h"

void EnemyBullet::Initialize(const Vec3& pos, const Vec3& velocity, Model* model, const UINT tex) {}

void EnemyBullet::Update() {}

void EnemyBullet::Draw(MatViewProjection& mVP) {}

void EnemyBullet::OnCollision(const int damange) { isDead = true; }

void EnemyBullet::Homing() 
{
	Vec3 fromVel = velocity;
	fromVel = fromVel.Normalized();

	Vec3 toPlayer = player->GetWorldPos() - obj.mW.pos;
	toPlayer.Normalized();

	velocity = Slerp(fromVel, toPlayer, inductive);
	velocity *= interval;
	obj.mW.rota = AdjustAngle(velocity);
}
