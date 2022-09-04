#include "SlashBullet.h"
#include "Math/Calc.h"

static const float INDUCTIVE = 0.001f;
static const float SPEED = 1.0f;
static const float RAD = 3.0f;

static const int32_t LIFE_T = 60 * 5;

void SlashBullet::Initialize(const Vec3& pos, const Vec3& velocity, Model* model, const UINT tex)
{
	this->velocity = velocity;
	this->model = model;
	this->tex = tex;
	obj.mW.pos = pos;
	obj.mW.scale = { 25.0f, 2.5f, 4.0f };
	obj.cbM.Color(GetColor({ 40, 235, 90, 255 }));
	obj.mW.rota = AdjustAngle(this->velocity);

	inductive = INDUCTIVE;
	speed = SPEED;

	SetDamage(20);

	SetRad(RAD);
	SetAttribute(COLL_ATTRIBUTE_ENEMY);
	SetMask(~COLL_ATTRIBUTE_ENEMY);

	deathT = LIFE_T;
	homT.Initialize(LIFE_T, 5);
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