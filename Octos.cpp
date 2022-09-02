#include "Octos.h"
#include "ScrewBullet.h"
#include "Player.h"
#include "Calc.h"
#include <cassert>

static const uint32_t TIME = 120;

void Octos::Initialize(const Vec3& pos, Model* model, const UINT tex)
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

	status.Initialize(15, 0);

	seekRad = 15.0f;
	SetRad(1.0f);
	SetAttribute(COLL_ATTRIBUTE_ENEMY);
	SetMask(~COLL_ATTRIBUTE_ENEMY);
}

void Octos::ModelInit()
{
	// body
	body[0].mW.scale = { 6.0,6.0,6.0 };
	body[0].cbM.Color(GetColor({ 220, 100, 50, 255 }));

	// head
	body[1].mW.scale = { 5.0,3.0,5.0 };
	body[1].mW.pos = { 0.0,6.0,0.0 };
	body[1].cbM.Color(GetColor({ 170, 70, 25, 255 }));

	// cheek
	body[2].mW.scale = { 2.0,3.0,3.0 };
	body[2].mW.pos = { 6.0,0.0,0.0 };
	body[2].cbM.Color(GetColor({ 220, 150, 50, 255 }));

	// cheek
	body[3].mW.scale = { 2.0,3.0,3.0 };
	body[3].mW.pos = { -6.0,0.0,0.0 };
	body[3].cbM.Color(GetColor({ 220, 150, 50, 255 }));

	// mouth
	body[4].mW.scale = { 3.0,2.0,2.0 };
	body[4].mW.pos = { 0.0,-2.0,6.0 };
	body[4].cbM.Color(GetColor({ 220, 150, 50, 255 }));

	// eye a
	body[5].mW.scale = { 1.5,1.5,1.0 };
	body[5].mW.pos = { 3.0,2.0,6.0 };
	body[5].cbM.Color(GetColor({ 255, 255, 255, 255 }));

	// eye b
	body[6].mW.scale = { 1.5,1.5,1.0 };
	body[6].mW.pos = { -3.0,2.0,6.0 };
	body[6].cbM.Color(GetColor({ 255, 255, 255, 255 }));

	// eye aa
	body[7].mW.scale = { 1.0,1.0,0.5 };
	body[7].mW.pos = { 3.0,2.0,7.0 };
	body[7].cbM.Color(GetColor({ 0, 0, 0, 255 }));

	// eye bb
	body[8].mW.scale = { 1.0,1.0,0.5 };
	body[8].mW.pos = { -3.0,2.0,7.0 };
	body[8].cbM.Color(GetColor({ 0, 0, 0, 255 }));

	// leg a
	body[9].mW.scale = { 1.0,4.0,1.0 };
	body[9].mW.pos = { 2.0,-6.0,2.0 };
	body[9].mW.rota = { PI / 8.0f,-PI / 8.0f,0.0f };
	body[9].cbM.Color(GetColor({ 220, 150, 50, 255 }));

	// leg b
	body[10].mW.scale = { 1.0,4.0,1.0 };
	body[10].mW.pos = { -2.0,-6.0,2.0 };
	body[10].mW.rota = { PI / 8.0f,PI / 8.0f,0.0f };
	body[10].cbM.Color(GetColor({ 220, 150, 50, 255 }));

	// leg c
	body[11].mW.scale = { 1.0,4.0,1.0 };
	body[11].mW.pos = { 2.0,-6.0,-2.0 };
	body[11].mW.rota = { PI / 8.0f,-PI / 4.0f,0.0f };
	body[11].cbM.Color(GetColor({ 220, 150, 50, 255 }));

	// leg d
	body[12].mW.scale = { 1.0,4.0,1.0 };
	body[12].mW.pos = { -2.0,-6.0,-2.0 };
	body[12].mW.rota = { PI / 8.0f,PI / 4.0f,0.0f };
	body[12].cbM.Color(GetColor({ 220, 150, 50, 255 }));
}

void Octos::Update()
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

void Octos::Draw(MatViewProjection& mVP)
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

void Octos::Fire()
{
	assert(player);

	Vec3 velocity = player->GetWorldPos();
	velocity -= GetWorldPos();
	velocity = velocity.Normalized();

	for (size_t i = 0; i < 8; i++)
	{
		std::unique_ptr<EnemyBullet> newBullet;
		newBullet = std::make_unique<ScrewBullet>();
		newBullet->Initialize2(obj.mW.pos, velocity, 1.5f, PI / 4 * i, model, tex);
		newBullet->SetPlayer(player);
		bullets.push_back(std::move(newBullet));
	}
}

void Octos::FireAndReset()
{
	Fire();
	timedCalls.push_back(std::make_unique<TimedCall>(
		std::bind(&Enemy::FireAndReset, this), TIME));
}
