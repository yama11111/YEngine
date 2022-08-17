#include "Object2D.h"
#include "Result.h"

Object2D::Object2D() :
	mW(MatWorld()), sprite(nullptr)
{
}

Object2D::Object2D(Sprite* pSprite) :
	mW(MatWorld()), sprite(pSprite)
{
}

void Object2D::SetSprite(Sprite* pSprite)
{
	this->sprite = pSprite;
}

void Object2D::Update()
{
	mW.Update();
}

void Object2D::Draw(const UINT tex)
{
	Result::Assert(sprite != nullptr);
	sprite->Draw(mW, tex);
}

