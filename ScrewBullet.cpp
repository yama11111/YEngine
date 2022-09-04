#include "ScrewBullet.h"
#include "Math/Calc.h"
#include "Player.h"

static const float INDUCTIVE = 0.01f;
static const float SPEED = 1.0f;
static const float RAD = 0.5f;

static const float SCALE = 3.0f;
static const float INC_RADIAN = PI / 18.0f;

static const int32_t LIFE_T = 60 * 5;

void ScrewBullet::Initialize2(	const Vec3& pos, const Vec3& velocity, 
								const float radius, const float radian, Model* model, const UINT tex)
{
	this->velocity = velocity;
	this->model = model;
	this->tex = tex;

	this->radian = radian;
	this->radius = radius;

	this->inductive = INDUCTIVE;
	this->speed = SPEED;

	obj.mW.pos = { cosf(radian),sinf(radian),0 };
	obj.mW.pos *= radius;
	obj.mW.scale = { SCALE, SCALE, SCALE };
	obj.cbM.Color(GetColor({ 245, 90, 25, 255 }));
	obj.SetParent(&nucleus);

	nucleus.pos = pos;
	//nucleus.rota = AdjustAngle(this->velocity);

	SetDamage(10);

	SetRad(RAD);
	SetAttribute(COLL_ATTRIBUTE_ENEMY);
	SetMask(~COLL_ATTRIBUTE_ENEMY);

	deathT = LIFE_T;
	homT.Initialize(LIFE_T, 5);
}

void ScrewBullet::Update()
{
	if (--deathT <= 0) isDead = true;
	Screw();
	Homing();
	nucleus.pos += velocity;
	nucleus.Update();
	obj.Update();

}

void ScrewBullet::Draw(MatViewProjection& mVP)
{
	model->Draw(obj, mVP, tex);
}

void ScrewBullet::Screw()
{
	radian -= INC_RADIAN;
	if (radian <= 0) radian = 2 * PI;

	obj.mW.pos = { cosf(radian),sinf(radian),0 };
	obj.mW.pos *= radius;
}

void ScrewBullet::Homing()
{
	homT.Update();
	if (homT.IsEnd())
	{
		isStraight = true;
	}
	if (!isStraight)
	{
		Vec3 fromVel = velocity;
		fromVel = fromVel.Normalized();

		Vec3 toPlayer = player->GetWorldPos() - nucleus.pos;
		toPlayer.Normalized();

		velocity = Lerp(fromVel, toPlayer, inductive);
		velocity = velocity.Normalized();
		//nucleus.rota = AdjustAngle(velocity);
		velocity *= speed;
	}
}


Vec3 ScrewBullet::GetWorldPos()
{
	Vec3 pos = nucleus.pos;
	//pos += obj.mW.pos;
	return pos;
}