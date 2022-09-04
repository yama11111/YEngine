#include "MonoEye.h"
#include "SphereBullet.h"
#include "Player.h"
#include "Math/Calc.h"
#include <cassert>

static const uint32_t TIME = 200;

void MonoEye::Initialize(const Vec3& pos, Model* model, const UINT tex)
{
	assert(model);
	this->model = model;
	this->tex = tex;

	obj.mW.pos = pos;
	obj.mW.scale = { 1.0f, 1.0f, 1.0f };
	for (size_t i = 0; i < ARY; i++)
	{
		body[i].SetParent(&draw.mW);
	}
	ModelInit();

	FireAndReset();

	status.Initialize(10, 0);

	seekRad = 15.0f;
	SetRad(1.0f);
	SetAttribute(COLL_ATTRIBUTE_ENEMY);
	SetMask(~COLL_ATTRIBUTE_ENEMY);
}

void MonoEye::ModelInit()
{
	// body
	body[0].mW.scale = { 7.5,7.5,7.5 };
	body[0].cbM.Color(GetColor({ 225, 50, 80, 255 }));

	// eye white
	body[1].mW.scale = { 5.0,5.0,5.0 };
	body[1].mW.pos = { 0.0,0.0,5.0 };
	body[1].cbM.Color(GetColor({ 255, 255, 255, 255 }));

	// eye blue
	body[2].mW.scale = { 2.0,3.0,2.0 };
	body[2].mW.pos = { 0.0f,0.0f,9.0 };
	body[2].cbM.Color(GetColor({ 0, 60, 140, 255 }));

	// tentacle a
	body[3].mW.scale = { 2.0,4.0,2.0 };
	body[3].mW.pos = { 5.0,-7.0,-8.0 };
	body[3].mW.rota = { PI / 8.0f,-PI / 8.0f,0.0f };
	body[3].cbM.Color(GetColor({ 240, 190, 130, 255 }));

	// tentacle b
	body[4].mW.scale = { 2.0,4.0,2.0 };
	body[4].mW.pos = { -5.0,-7.0,-8.0 };
	body[4].mW.rota = { PI / 8.0f,PI / 8.0f,0.0f };
	body[4].cbM.Color(GetColor({ 240, 190, 130, 255 }));

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
	draw = GetObjD();
	model->Draw(draw, mVP, tex);
	for (size_t i = 0; i < ARY; i++)
	{
		body[i].Update();
		model->Draw(body[i], mVP, tex);
	}
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
	newBullet->Initialize(obj.mW.pos, velocity, model, tex);
	newBullet->SetPlayer(player);
	bullets.push_back(std::move(newBullet));
}

void MonoEye::FireAndReset()
{
	Fire();
	timedCalls.push_back(std::make_unique<TimedCall>(
		std::bind(&Enemy::FireAndReset, this), TIME));
}
