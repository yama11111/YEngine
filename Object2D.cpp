#include "Object2D.h"

Object2D::Object2D(const Vec2& size) :
	mW(MatWorld()), sprite(Sprite(size))
{
}

void Object2D::Update()
{
	mW.Update();
}

void Object2D::Draw(const UINT tex)
{
	sprite.Draw(mW, tex);
}

