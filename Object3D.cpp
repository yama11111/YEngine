#include "Object3D.h"
#include "Result.h"

ConstBufferManager* Object3D::cbManager = nullptr;

Object3D::Object3D() :
	mW(MatWorld())
{
	cbManager->CreateCB(cbM);
	cbManager->CreateCB(cbT);
}

void Object3D::Update()
{
	mW.Update();
	if (parent)
	{
		mW.m *= parent->m;
	}
}

void Object3D::SetCommand()
{
	cbManager->SetCommand(cbM);
	cbManager->SetCommand(cbT);
}

void Object3D::Affine(MatViewProjection& mVP)
{
	cbT.cMapTrfm->mat = mW.m * mVP.view.m * mVP.pro.m;
}

void Object3D::SetParent(MatWorld* parent)
{
	if (parent == nullptr) return;
	this->parent = parent;
}

void Object3D::StaticInit()
{
	cbManager = ConstBufferManager::GetInstance();
}