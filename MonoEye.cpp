#include "MonoEye.h"
#include "SphereBullet.h"
#include "Player.h"
#include "Calc.h"
#include <cassert>

static const uint32_t TIME = 200;

void MonoEye::Initialize(const Vec3& pos, Model* model, const UINT tex, const UINT bulletTex)
{
	assert(model);
	this->model = model;
	this->tex = tex;
	this->bulletTex = bulletTex;

	obj.mW.pos = pos;
	obj.mW.scale = { 5.0, 5.0, 5.0 };
	FireAndReset();

	status.Initialize(10, 0);

	seekRad = 15.0f;
	SetRad(1.0f);
	SetAttribute(COLL_ATTRIBUTE_ENEMY);
	SetMask(~COLL_ATTRIBUTE_ENEMY);
}

void MonoEye::Update()
{
	timedCalls.remove_if([](std::unique_ptr<TimedCall>& timedCall) {return timedCall->IsFinished(); });
	bullets.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {return bullet->IsDead(); });

	for (std::unique_ptr<TimedCall>& timedCall : timedCalls)
	{
		timedCall->Update();
	}

	shake.Update();
	HitAnimation();
	DeathAnimation();

	FollowEyes();

	obj.Update();

	for (std::unique_ptr<EnemyBullet>& bullet : bullets)
	{
		bullet->Update();
	}

	SetTarget();
}

void MonoEye::Draw(MatViewProjection& mVP)
{
	Object3D o = GetObjD();
	model->Draw(o, mVP, tex);
	for (std::unique_ptr<EnemyBullet>& bullet : bullets)
	{
		bullet->Draw(mVP);
	}
}

void MonoEye::Fire()
{
	assert(player);

	Vec3 velocity = player->GetWorldPos();
	velocity -= GetWorldPos();
	velocity = velocity.Normalized();

	std::unique_ptr<EnemyBullet> newBullet;
	newBullet = std::make_unique<SphereBullet>();
	newBullet->Initialize(obj.mW.pos, velocity, model, bulletTex);
	newBullet->SetPlayer(player);
	bullets.push_back(std::move(newBullet));
}

void MonoEye::FireAndReset()
{
	Fire();
	timedCalls.push_back(std::make_unique<TimedCall>(
		std::bind(&Enemy::FireAndReset, this), TIME));
}
