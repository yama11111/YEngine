#include "Object2D.h"

DX::GPUResource::ConstBufferManager* Object2D::cbManager = nullptr;

void Object2D::StaticInit()
{
	cbManager = DX::GPUResource::ConstBufferManager::GetInstance();
}

Object2D::Object2D() :
	mW(MatWorld())
{
	cbManager->CreateCB(cbM);
	cbManager->CreateCB(cbT);
}

void Object2D::Update()
{
	mW.Update();
	if (parent)
	{
		mW.m *= parent->m;
	}
}

void Object2D::SetCommand()
{
	cbManager->SetCommand(cbM);
	cbManager->SetCommand(cbT);
}

void Object2D::SetParent(MatWorld* parent)
{
	if (parent == nullptr) return;
	this->parent = parent;
}

