#include "Enemy.h"
#include "SphereBullet.h"
#include "SlashBullet.h"
#include "ScrewBullet.h"
#include "Player.h"
#include "Calc.h"
#include <cassert>

void Enemy::Initialize(const Vec3& pos, const int& species,
	Model* model, const UINT tex, const UINT bulletTex)
{
	assert(model);
	this->model = model;
	this->tex = tex;
	this->bulletTex = bulletTex;
	this->species = species;
	obj.mW.pos = pos;
	obj.mW.scale = { 5.0, 5.0, 5.0 };
	FireAndReset();
	seekRad = 15.0f;
	SetRad(1.0f);
	SetAttribute(COLL_ATTRIBUTE_ENEMY);
	SetMask(~COLL_ATTRIBUTE_ENEMY);
}

void Enemy::Update() 
{
	timedCalls.remove_if([](std::unique_ptr<TimedCall>& timedCall) {return timedCall->IsFinished(); });

	for (std::unique_ptr<TimedCall>& timedCall : timedCalls) 
	{
		timedCall->Update();
	}

	bullets.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {return bullet->IsDead(); });

	(this->*spUpdateTable[static_cast<size_t>(phase)])();
	obj.Update();

	for (std::unique_ptr<EnemyBullet>& bullet : bullets) 
	{
		bullet->Update();
	}
}

void Enemy::Draw(MatViewProjection& mVP)
{
	model->Draw(obj, mVP, tex);
	for (std::unique_ptr<EnemyBullet>& bullet : bullets) 
	{
		bullet->Draw(mVP);
	}
}

Vec3 Enemy::GetWorldPos() 
{
	Vec3 pos = obj.mW.pos;
	return pos;
}

void Enemy::Approach() 
{
	const float SPEED = -0.05f;
	Vec3 velocity = { 0, 0, SPEED };
	//obj.mW.pos += velocity;
}

void Enemy::OnCollision(const int damage)
{ 
	obj.cbM.Color({ 1.0,0.0,0.0,1.0 }); 
}

void Enemy::Leave() 
{
	const float SPEED = 1.0f;
	Vec3 velocity = { 0, 0, SPEED };
	obj.mW.pos += velocity;
}

void Enemy::Fire() 
{
	assert(player);

	const float SPEED = -0.5f;

	Vec3 velocity = GetWorldPos();
	velocity -= player->GetWorldPos();
	velocity = velocity.Normalized();
	velocity *= SPEED;

	std::unique_ptr<EnemyBullet> newBullet;
	switch (species)
	{
	case Species::MonoEye:
	default:
		newBullet = std::make_unique<SphereBullet>();
		break;
	case Species::WaveAngler:
		newBullet = std::make_unique<SlashBullet>();
		break;
	case Species::Croan:
		newBullet = std::make_unique<ScrewBullet>();
		break;
	}
	newBullet->Initialize(obj.mW.pos, velocity, model, bulletTex);
	newBullet->SetPlayer(player);
	bullets.push_back(std::move(newBullet));
}

void Enemy::FireAndReset() 
{
	Fire();
	uint32_t time = 0;
	switch (species)
	{
	case Species::MonoEye:
	default:
		time = 80;
		break;
	case Species::WaveAngler:
		time = 120;
		break;
	case Species::Croan:
		time = 60;
		break;
	}
	timedCalls.push_back(std::make_unique<TimedCall>(
		std::bind(&Enemy::FireAndReset, this), time));

}

void (Enemy::* Enemy::spUpdateTable[])() = {
	&Enemy::Approach,
	&Enemy::Leave,
};