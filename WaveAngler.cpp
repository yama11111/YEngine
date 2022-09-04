#include "WaveAngler.h"
#include "SlashBullet.h"
#include "Player.h"
#include "Math/Calc.h"
#include <cassert>

static const uint32_t TIME = 300;

void WaveAngler::Initialize(const Vec3& pos, Model* model, const UINT tex)
{
	assert(model);
	this->model = model;
	this->tex = tex;

	obj.mW.pos = pos;
	obj.mW.scale = { 1.0, 1.0, 1.0 };
	for (size_t i = 0; i < ARY; i++)
	{
		body[i].SetParent(&draw.mW);
	}
	ModelInit();

	FireAndReset();

	status.Initialize(25, 0);

	seekRad = 15.0f;
	SetRad(1.0f);
	SetAttribute(COLL_ATTRIBUTE_ENEMY);
	SetMask(~COLL_ATTRIBUTE_ENEMY);
}

void WaveAngler::ModelInit()
{
	// body
	body[0].mW.scale = { 12.0,3.0,12.0 };
	body[0].cbM.Color(GetColor({ 150, 190, 30, 255 }));

	// eye a
	body[1].mW.scale = { 4.0,4.0,4.0 };
	body[1].mW.pos = { 10.0,2.0,10.0 };
	body[1].cbM.Color(GetColor({ 80, 150, 30, 255 }));

	// eye b
	body[2].mW.scale = { 4.0,4.0,4.0 };
	body[2].mW.pos = { -10.0,2.0,10.0 };
	body[2].cbM.Color(GetColor({ 80, 150, 30, 255 }));

	// fin a
	body[3].mW.scale = { 4.0,2.0,6.0 };
	body[3].mW.pos = { 15.0,0.0,0.0 };
	body[3].cbM.Color(GetColor({ 150, 190, 30, 255 }));

	// fin b
	body[4].mW.scale = { 4.0,2.0,6.0 };
	body[4].mW.pos = { -15.0,0.0,0.0 };
	body[4].cbM.Color(GetColor({ 150, 190, 30, 255 }));

	// fin c
	body[5].mW.scale = { 6.0,2.0,10.0 };
	body[5].mW.pos = { 0.0,0.0,-10.0 };
	body[5].cbM.Color(GetColor({ 220, 70, 120, 255 }));

	// fin d
	body[6].mW.scale = { 2.0,8.0,6.0 };
	body[6].mW.pos = { 0.0,6.0,0.0 };
	body[6].cbM.Color(GetColor({ 220, 70, 120, 255 }));
}

void WaveAngler::Update()
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

void WaveAngler::Draw(MatViewProjection& mVP)
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

void WaveAngler::Fire()
{
	assert(player);

	Vec3 velocity = player->GetWorldPos();
	velocity -= GetWorldPos();
	velocity = velocity.Normalized();

	std::unique_ptr<EnemyBullet> newBullet;
	newBullet = std::make_unique<SlashBullet>();
	newBullet->Initialize(obj.mW.pos, velocity, model, tex);
	newBullet->SetPlayer(player);
	bullets.push_back(std::move(newBullet));
}

void WaveAngler::FireAndReset()
{
	Fire();
	timedCalls.push_back(std::make_unique<TimedCall>(
		std::bind(&Enemy::FireAndReset, this), TIME));
}
