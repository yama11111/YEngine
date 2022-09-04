#include "RailCamera.h"
#include "Math/Calc.h"

void RailCamera::Initialize(const Vec3& pos)
{
	mW.pos = pos;
	power = 0.1f;
	speed.Initialize({}, power);
	shake.Initialize();
}

void RailCamera::Update()
{
	Move();
	Rotate();
	mW.Update();
	shake.Update();
	vpUpdate();
}

void RailCamera::Shaking(const float swing, const float dekey)
{
	shake.Shaking(swing, dekey);
}

MatViewProjection RailCamera::GetViewProjectionD()
{
	MatViewProjection r = vp;
	r.view.eye += shake.GetValue();
	r.view.target += shake.GetValue();
	return r;
}

void RailCamera::Move()
{
	speed.Update(false);
	mW.pos += speed.value;
}

void RailCamera::Rotate()
{

}

void RailCamera::vpUpdate()
{
	vp.view.eye = mW.pos;
	Vec3 forward(0, 0, 1);
	forward = MultVec3Mat4(forward, mW.m);
	vp.view.target = vp.view.eye;
	vp.view.target += forward;
	Vec3 up(0, 1, 0);
	vp.view.up = MultVec3Mat4(up, mW.m);
	vp.Update();
}
