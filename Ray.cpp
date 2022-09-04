#include "Ray.h"
#include "Math/Calc.h"
#include <cassert>

void Ray::Initialize(const InitRay& init, Model* model, const UINT tex)
{
	assert(model);
	this->start = init.start;
	this->velocity = init.velocity;
	this->velocity = this->velocity.Normalized();
	this->length = init.length;
	this->model = model;
	this->tex = tex;
}

void Ray::InitState(const InitRay& init)
{
	this->start = init.start;
	this->velocity = init.velocity;
	this->velocity = this->velocity.Normalized();
	this->length = init.length;
}

void Ray::Update()
{
	Adjust();
	obj.Update();
}

void Ray::SetStart(const Vec3& start)
{
	this->start = start;
}

void Ray::SetVelocity(const Vec3& velocity)
{
	this->velocity = velocity.Normalized();
}

void Ray::SetLength(const float length)
{
	this->length = length;
}

void Ray::Draw(MatViewProjection& vP)
{
	model->Draw(obj, vP, tex);
}

Ray::Ray() :
	start({})
{
}

void Ray::Adjust()
{
	obj.mW.pos = start;
	Vec3 move = velocity;
	move *= (length / 2.0f);
	obj.mW.pos += move;
	obj.mW.scale.z = length;

	obj.mW.rota = AdjustAngle(velocity);
}
