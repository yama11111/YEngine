#pragma once
#include "Object2D.h"
#include "Vertices.h"
#include "TextureManager.h"
#include "MatProjection.h"

class Sprite
{
public:
	const Vec2 size;
private:
	Vertices2D vt;
public:
	Sprite(const Vec2& size);
	void Draw(Object2D& obj, const UINT tex);
private:
	static MatProjection mP;
	static TextureManager* texManager;
public:
	static void StaticInit();
};
