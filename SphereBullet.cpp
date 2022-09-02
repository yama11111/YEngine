#include "SphereBullet.h"
#include "Calc.h"

static const float INDUCTIVE = 0.0005f;
static const float SPEED = 2.0f;
static const float RAD = 3.0f;

static const int32_t LIFE_T = 60 * 5;

void SphereBullet::Initialize(const Vec3& pos, const Vec3& velocity, Model* model, const UINT tex)
{
	this->velocity = velocity;
	this->model = model;
	this->tex = tex;
	obj.mW.pos = pos;
	obj.mW.scale = { 5.0f, 5.0f, 5.0f };
	obj.cbM.Color(GetColor( { 90, 15, 95, 255 }));
	obj.mW.rota = AdjustAngle(this->velocity);

	inductive = INDUCTIVE;
	speed = SPEED;

	SetDamage(5);

	SetRad(RAD);
	SetAttribute(COLL_ATTRIBUTE_ENEMY);
	SetMask(~COLL_ATTRIBUTE_ENEMY);

	deathT = LIFE_T;
	homT.Initialize(LIFE_T, 5);
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

