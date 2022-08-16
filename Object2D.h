#pragma once
#include "Sprite.h"

class Object2D
{
public:
	MatWorld mW;
	Sprite sprite;
public:
	Object2D(const Vec2& size);
	void Update();
	void Draw(const UINT tex);
	void Affine();
};
