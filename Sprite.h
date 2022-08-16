#pragma once
#include "VertexIndex.h"
#include "ConstBufferManager.h"
#include "TextureManager.h"
#include "MatWorld.h"
#include "MatProjection.h"

class Sprite
{
public:
	ConstBufferMaterial cbM;
	ConstBufferTransform cbT;
private:
	VertexIndex vtIdx;
public:
	Sprite(const Vec2& size);
	void Draw(MatWorld& mW, const UINT tex);
private:
	static MatProjection mP;
	static ConstBufferManager* cbManager;
	static TextureManager* texManager;
public:
	static void StaticInit();
};
