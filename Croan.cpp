#include "Croan.h"
#include "ScrewBullet.h"
#include "Player.h"
#include "Calc.h"
#include <cassert>

static const uint32_t TIME = 60;

void Croan::Initialize(const Vec3& pos, Model* model, const UINT tex)
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

void Croan::ModelInit()
{
	// body
	body[0].mW.scale = { 8.0,9.0,7.0 };
	body[0].cbM.Color(GetColor({ 60, 150, 60, 255 }));

	// eye a
	body[1].mW.scale = { 4.0,4.0,2.0 };
	body[1].mW.pos = { 0.0,3.0,7.0 };
	body[1].cbM.Color(GetColor({ 190, 65, 25, 255 }));

	// eye b
	body[2].mW.scale = { 2.0,3.0,1.0 };
	body[2].mW.pos = { 0.0f,3.0f,9.0 };
	body[2].cbM.Color(GetColor({ 0, 0, 0, 255 }));

	// wing a
	body[3].mW.scale = { 8.0,2.0,6.0 };
	body[3].mW.pos = { 8.0,9.0,-2.0 };
	body[3].mW.rota = { 0.0f,0.0f,PI / 8.0f };
	body[3].cbM.Color(GetColor({ 255, 255, 255, 255 }));

	// wing b
	body[4].mW.scale = { 8.0,2.0,6.0 };
	body[4].mW.pos = { -8.0,9.0,-2.0 };
	body[4].mW.rota = { 0.0f,0.0f,-PI / 8.0f };
	body[4].cbM.Color(GetColor({ 255, 255, 255, 255 }));

	// reg a
	body[5].mW.scale = { 4.0,6.0,4.0 };
	body[5].mW.pos = { 6.0,-10.0,-1.0 };
	body[5].mW.rota = { -PI / 4.0f,0.0f,0.0f };
	body[5].cbM.Color(GetColor({ 100, 185, 50, 255 }));

	// reg b
	body[6].mW.scale = { 4.0,6.0,4.0 };
	body[6].mW.pos = { -6.0,-10.0,-1.0 };
	body[6].mW.rota = { -PI / 4.0f,0.0f,0.0f };
	body[6].cbM.Color(GetColor({ 100, 185, 50, 255 }));

	// reg aa
	body[7].mW.scale = { 3.0,6.0,2.0 };
	body[7].mW.pos = { 6.0,-15.0,-2.0 };
	body[7].mW.rota = { PI / 4.0f,0.0f,0.0f };
	body[7].cbM.Color(GetColor({ 100, 185, 50, 255 }));

	// reg bb
	body[8].mW.scale = { 3.0,6.0,2.0 };
	body[8].mW.pos = { -6.0,-15.0,-2.0 };
	body[8].mW.rota = { PI / 4.0f,0.0f,0.0f };
	body[8].cbM.Color(GetColor({ 100, 185, 50, 255 }));
}

void Croan::Update()
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

void Croan::Draw(MatViewProjection& mVP)
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

void Croan::Fire()
{
	assert(player);

	Vec3 velocity = player->GetWorldPos();
	velocity -= GetWorldPos();
	velocity = velocity.Normalized();

	std::unique_ptr<EnemyBullet> newBullet;
	newBullet = std::make_unique<ScrewBullet>();
	newBullet->Initialize2(obj.mW.pos, velocity, 10.0f, 0.0f, model, tex);
	newBullet->SetPlayer(player);
	bullets.push_back(std::move(newBullet));
}

void Croan::FireAndReset()
{
	Fire();
	timedCalls.push_back(std::make_unique<TimedCall>(
		std::bind(&Enemy::FireAndReset, this), TIME));
}
