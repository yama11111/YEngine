#include "Object3D.h"

Object3D::Object3D() :
	mW(MatWorld()), model(Model())
{
}

void Object3D::Update()
{
	mW.Update();
}

void Object3D::Draw(MatViewProjection& mVP, const UINT tex)
{
	model.Draw(mW, mVP, tex);
}
