#include "SlashBullet.h"
#include "Calc.h"

void SlashBullet::Initialize(const Vec3& pos, const Vec3& velocity, Model* model, const UINT tex)
{
	this->velocity = velocity;
	this->model = model;
	this->tex = tex;
	obj.mW.pos = pos;
	obj.mW.scale = { 3.0f, 0.25f, 0.5f };
	obj.cbM.Color({ 0.25,0.5,0.75,1.0 });
	obj.mW.rota = AdjustAngle(this->velocity);
	SetRad(3.0f);
	SetAttribute(COLL_ATTRIBUTE_ENEMY);
	SetMask(~COLL_ATTRIBUTE_ENEMY);
}

void SlashBullet::Update()
{
	if (--deathT <= 0) isDead = true;
	Homing();
	obj.mW.pos += velocity;
	obj.Update();
}

void SlashBullet::Draw(MatViewProjection& mVP)
{
	model->Draw(obj, mVP, tex);
}

Vec3 SlashBullet::GetWorldPos()
{
	Vec3 pos = obj.mW.pos;
	return pos;
}
