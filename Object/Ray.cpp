#include "Ray.h"
#include "Calc.h"
#include <cassert>

using Object::Ray;

void Ray::Initialize(const InitRay& init, Model* model, const UINT tex)
{
	assert(model);
	InitState(init);
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
	trfm.Update();
}

void Ray::Adjust()
{
	//Math::Vec3 move = velocity * (length / 2.0f);
	//trfm.mW.pos = start + move;
	trfm.mW.scale.z = length;

	trfm.mW.rota = AdjustAngle(velocity);
}

void Ray::Draw(MatViewProjection& vp)
{
	model->Draw(trfm, vp, tex);
}

void Ray::SetStart(const Math::Vec3& start)
{
	this->start = start;
}

void Ray::SetVelocity(const Math::Vec3& velocity)
{
	this->velocity = velocity.Normalized();
}

void Ray::SetLength(const float length)
{
	this->length = length;
}
