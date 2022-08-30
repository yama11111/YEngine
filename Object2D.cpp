#include "Object2D.h"
#include "Result.h"

ConstBufferManager* Object2D::cbManager = nullptr;

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

void Object2D::StaticInit()
{
	cbManager = ConstBufferManager::GetInstance();
}

