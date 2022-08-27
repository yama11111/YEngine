#include "ScrewBullet.h"
#include "Calc.h"
#include "Player.h"

void ScrewBullet::Initialize(const Vec3& pos, const Vec3& velocity, Model* model, const UINT tex)
{
	this->velocity = velocity;
	this->model = model;
	this->tex = tex;

	parent.pos = pos;
	parent.rota = AdjustAngle(this->velocity);

	Screw();
	const float S = 2.5f;

	obj.mW.scale = { S, S, S };
	obj.cbM.Color({ 0.75,0.75,1.0,1.0 });
	obj.SetParent(&parent);

	obj2.mW.scale = { S, S, S };
	obj2.cbM.Color({ 0.75,0.75,1.0,1.0 });
	obj2.SetParent(&parent);

	SetRad(3.0f);
	SetAttribute(COLL_ATTRIBUTE_ENEMY);
	SetMask(~COLL_ATTRIBUTE_ENEMY);
}

void ScrewBullet::Update()
{
	if (--deathT <= 0) isDead = true;
	if (rad < 2 * PI) rad += PI / 30.0f;
	else rad = 0.0f;
	Homing();
	Screw();
	parent.pos += velocity;
	parent.Update();
	obj.Update();
	obj2.Update();
}

void ScrewBullet::Draw(MatViewProjection& mVP)
{
	model->Draw(obj, mVP, tex);
	model->Draw(obj2, mVP, tex);
}

Vec3 ScrewBullet::GetWorldPos()
{
	Vec3 pos = parent.pos;
	return pos;
}

void ScrewBullet::Screw()
{
	Vec3 shaft = { cosf(rad),sinf(rad),0};
	Vec3 v = shaft.Cross(velocity);
	v *= 10.0f;
	obj.mW.pos = v;
	v *= -1.0f;
	obj2.mW.pos = v;
}

void ScrewBullet::Homing()
{
	Vec3 fromVel = velocity;
	fromVel = fromVel.Normalized();

	Vec3 toPlayer = player->GetWorldPos() - parent.pos;
	toPlayer.Normalized();

	velocity = Slerp(fromVel, toPlayer, inductive);
	velocity *= interval;
	parent.rota = AdjustAngle(velocity);
}
