#include "PlayerBullet.h"
#include "Calc.h"

static const float SCALE1 = 2.5f;
static const float SCALE2 = 10.0f;

void PlayerBullet::Initialize(	const Vec3& pos, const Vec3& velocity, const bool charge,
								Model* model, const UINT tex)
{
	this->model = model;
	this->tex = tex;
	obj.mW.pos = pos;
	this->velocity = velocity;
	this->charge = charge;

	if (charge) obj.mW.scale = { SCALE2 / 1.25f, SCALE2 / 1.25f, SCALE2 };
	else obj.mW.scale = { SCALE1, SCALE1, SCALE1 };

	if (charge) obj.cbM.Color(GetColor({ 175, 0, 235, 255 }));
	else obj.cbM.Color(GetColor({ 175, 0, 235, 255 }));

	if (charge) SetRad(25.0f);
	else SetRad(10.0f);

	if (charge) SetDamage(20);
	else SetDamage(2);

	SetAttribute(COLL_ATTRIBUTE_PLAYER);
	SetMask(~COLL_ATTRIBUTE_PLAYER);
}

void PlayerBullet::Update() 
{
	if (--deathT <= 0) isDead = true;
	obj.mW.pos += velocity;
	obj.mW.rota = AdjustAngle(velocity);
	obj.Update();
}

void PlayerBullet::Draw(MatViewProjection& mVP) 
{
	model->Draw(obj, mVP, tex);
}

void PlayerBullet::OnCollision(const int damange) 
{ 
	isDead = !charge; 
}

Vec3 PlayerBullet::GetWorldPos() 
{
	Vec3 pos = obj.mW.pos;
	return pos;
}
