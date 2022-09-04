#pragma once
#include "Object3D.h"
#include "YDirectX/GPUResource/VertexIndex.h"
#include "YDirectX/GPUResource/TextureManager.h"

class Model
{
private:
	DX::GPUResource::VertexIndex vtIdx;
public:
	Model();
	void Draw(Object3D& obj, MatViewProjection& mVP, const UINT tex);
private:
	static DX::GPUResource::TextureManager* texManager;
public:
	static void StaticInit();
};
