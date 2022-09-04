#pragma once
#include "Object2D.h"
#include "YDirectX/GPUResource/Vertices2D.h"
#include "YDirectX/GPUResource/TextureManager.h"
#include "MatProjection.h"

class Sprite
{
public:
	const Vec2 size;
private:
	DX::GPUResource::Vertices2D vt;
public:
	Sprite(const Vec2& size);
	void Draw(Object2D& obj, const UINT tex);
private:
	static MatProjection mP;
	static DX::GPUResource::TextureManager* texManager;
public:
	static void StaticInit();
};
