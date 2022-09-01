#include "CircleBullet.h"
#include "Calc.h"

static const float INDUCTIVE = 0.01f;
static const float SPEED = 1.0f;
static const float RAD = 0.5f;

static const float SCALE = 30.0f;
static const Vec3 INC_SCALE = { 0.1f, 0.1f, 0.1f };
static const float INC_RADIAN = PI / 36.0f;

static const int32_t LIFE_T = 60 * 10;


void CircleBullet::Initialize2( const Vec3& pos, const Vec3& velocity, 
								const float radius, const float radian, Model* model, const UINT tex)
{
	this->velocity = velocity;
	this->model = model;
	this->tex = tex;

	this->speed = SPEED;
	this->velocity *= speed;

	this->radian = radian;
	this->radius = radius;

	obj.mW.pos = { cosf(radian),sinf(radian),0 };
	obj.mW.pos *= radius;
	obj.mW.scale = { 0.5f, 0.5f, 0.5f };
	obj.cbM.Color({ 0.75,0.75,1.0,1.0 });
	obj.SetParent(&nucleus);

	nucleus.pos = pos;
	//nucleus.rota = AdjustAngle(this->velocity);

	SetDamage(15);

	SetRad(RAD);
	SetAttribute(COLL_ATTRIBUTE_ENEMY);
	SetMask(~COLL_ATTRIBUTE_ENEMY);

	deathT = LIFE_T;
}

void CircleBullet::Update()
{
	if (--deathT <= 0) isDead = true;
	Screw();
	nucleus.pos += velocity;
	if (nucleus.scale.x <= SCALE)
	{
		nucleus.scale += INC_SCALE;
		if (nucleus.scale.x >= SCALE)
		{
			nucleus.scale.x = SCALE;
			nucleus.scale.y = SCALE;
			nucleus.scale.z = SCALE;
		}
	}
	nucleus.Update();
	obj.Update();
}

void CircleBullet::Draw(MatViewProjection& mVP)
{
	model->Draw(obj, mVP, tex);
}

void CircleBullet::Screw()
{
	radian -= INC_RADIAN;
	if (radian <= 0) radian = 2 * PI;

	obj.mW.pos = { cosf(radian),sinf(radian),0 };
	obj.mW.pos *= radius;
}

Vec3 CircleBullet::GetWorldPos()
{
	Vec3 pos = nucleus.pos;
	pos += obj.mW.pos;
	return pos;
}