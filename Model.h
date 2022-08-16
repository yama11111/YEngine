#pragma once
#include "VertexIndex.h"
#include "ConstBufferManager.h"
#include "TextureManager.h"
#include "MatWorld.h"
#include "MatViewProjection.h"

class Model
{
public:
	ConstBufferMaterial cbM;
	ConstBufferTransform cbT;
private:
	VertexIndex vtIdx;
public:
	Model();
	void Draw(MatWorld& mW, MatViewProjection& mVP, const UINT tex);
private:
	static ConstBufferManager* cbManager;
	static TextureManager* texManager;
public:
	static void StaticInit();
};
