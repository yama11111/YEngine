#include "Object3D.h"
#include "Result.h"

Object3D::Object3D() :
	mW(MatWorld()), model(nullptr)
{
}

Object3D::Object3D(Model* pModel) :
	mW(MatWorld()), model(pModel)
{
}

void Object3D::SetModel(Model* pModel)
{
	this->model = pModel;
}

void Object3D::Update()
{
	mW.Update();
}

void Object3D::Draw(MatViewProjection& mVP, const UINT tex)
{
	Result::Assert(model != nullptr);
	model->Draw(mW, mVP, tex);
}
