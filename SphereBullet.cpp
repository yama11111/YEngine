#include "SphereBullet.h"
#include "Calc.h"

void SphereBullet::Initialize(const Vec3& pos, const Vec3& velocity, Model* model, const UINT tex)
{
	this->velocity = velocity;
	this->model = model;
	this->tex = tex;
	obj.mW.pos = pos;
	obj.mW.scale = { 5.0f, 5.0f, 5.0f };
	obj.cbM.Color({ 0.25,0.0,0.25,1.0 });
	obj.mW.rota = AdjustAngle(this->velocity);
	SetRad(3.0f);
	SetAttribute(COLL_ATTRIBUTE_ENEMY);
	SetMask(~COLL_ATTRIBUTE_ENEMY);
}

void SphereBullet::Update()
{
	if (--deathT <= 0) isDead = true;
	Homing();
	obj.mW.pos += velocity;
	obj.Update();
}

void SphereBullet::Draw(MatViewProjection& mVP)
{
	model->Draw(obj, mVP, tex);
}

Vec3 SphereBullet::GetWorldPos()
{
	Vec3 pos = obj.mW.pos;
	return pos;
}
