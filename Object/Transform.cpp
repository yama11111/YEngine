#include "Transform.h"

using Object::Transform;

DX::GPUResource::ConstBufferManager* Transform::cbManager = nullptr;

void Transform::StaticInit()
{
	cbManager = DX::GPUResource::ConstBufferManager::GetInstance();
}

Transform::Transform() :
	mW(MatWorld())
{
	cbManager->CreateCB(cbM);
	cbManager->CreateCB(cbT);
}

void Transform::Update()
{
	mW.Update();
	if (parent)
	{
		mW.m *= parent->m;
	}
}

void Transform::SetCommand()
{
	cbManager->SetCommand(cbM);
	cbManager->SetCommand(cbT);
}

void Transform::Affine(Math::Mat4& view, Math::Mat4& projection)
{
	cbT.mapTrfm->mat = mW.m * view * projection;
}

void Transform::SetParent(MatWorld* parent)
{
	if (parent == nullptr) return;
	this->parent = parent;
}