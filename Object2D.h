#pragma once
#include "Sprite.h"

class Object2D
{
public:
	MatWorld mW;
	Sprite* sprite;
public:
	Object2D();
	Object2D(Sprite* pSprite);
	void SetSprite(Sprite* pSprite);
	void Update();
	void Draw(const UINT tex);
};
