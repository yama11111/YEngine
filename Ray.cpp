#include "Ray.h"
#include "Calc.h"
#include <cassert>

void Ray::Initialize(Vec3& start, Vec3& velocity, Model* model, const UINT tex)
{
	assert(model);
	this->start = start;
	this->velocity = velocity;
	this->model = model;
	this->tex = tex;
}

void Ray::Update()
{
	Adjust();
	obj.Update();
}

void Ray::SetStart(Vec3& start)
{
	this->start = start;
}

void Ray::SetVelocity(Vec3& velocity)
{
	this->velocity = velocity;
}

void Ray::Draw(MatViewProjection& vP)
{
	model->Draw(obj, vP, tex);
}

void Ray::Adjust()
{
	obj.mW.pos = start;
	obj.mW.pos.x = velocity.x * obj.mW.scale.x;
	obj.mW.pos.y = velocity.y * obj.mW.scale.y;
	obj.mW.pos.z = velocity.z * obj.mW.scale.z;

	obj.mW.rota = AdjustAngle(velocity);
}
