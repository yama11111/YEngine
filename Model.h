#pragma once
#include "Object3D.h"
#include "VertexIndex.h"
#include "TextureManager.h"

class Model
{
private:
	VertexIndex vtIdx;
public:
	Model();
	void Draw(Object3D& obj, MatViewProjection& mVP, const UINT tex);
private:
	static TextureManager* texManager;
public:
	static void StaticInit();
};
