#pragma once
#include "YDirectX/GPUResource/ConstBufferManager.h"
#include "MatWorld.h"
#include "MatViewProjection.h"

class Object3D
{
public:
	MatWorld mW;
	DX::GPUResource::ConstBufferMaterial cbM;
	DX::GPUResource::ConstBufferTransform cbT;
	MatWorld* parent = nullptr;
public:
	Object3D();
	void Update();
	void SetCommand();
	void Affine(MatViewProjection& mVP);
	void SetParent(MatWorld* parent);
private:
	static DX::GPUResource::ConstBufferManager* cbManager;
public:
	static void StaticInit();
};
