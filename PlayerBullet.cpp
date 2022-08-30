#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vec3& pos, const Vec3& velocity, const UINT tex)
{
	this->model = model;
	this->tex = tex;
	obj.mW.pos = pos;
	obj.mW.scale = { 2.5f, 2.5f, 2.5f };
	obj.cbM.Color({ 1.0,0.0,1.0,1.0 });
	this->velocity = velocity;
	SetRad(5.0f);
	SetAttribute(COLL_ATTRIBUTE_PLAYER);
	SetMask(~COLL_ATTRIBUTE_PLAYER);
}

void PlayerBullet::Update() 
{
	if (--deathT <= 0) isDead = true;
	obj.mW.pos += velocity;
	obj.Update();
}

void PlayerBullet::Draw(MatViewProjection& mVP) 
{
	model->Draw(obj, mVP, tex);
}

void PlayerBullet::OnCollision(const int damange) { isDead = true; }

Vec3 PlayerBullet::GetWorldPos() 
{
	Vec3 pos = obj.mW.pos;
	return pos;
}
