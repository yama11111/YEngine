#pragma once
#include "ConstBufferManager.h"
#include "MatWorld.h"
#include "MatViewProjection.h"

class Object3D
{
public:
	MatWorld mW;
	ConstBufferMaterial cbM;
	ConstBufferTransform cbT;
	MatWorld* parent = nullptr;
public:
	Object3D();
	void Update();
	void SetCommand();
	void Affine(MatViewProjection& mVP);
	void SetParent(MatWorld* parent);
private:
	static ConstBufferManager* cbManager;
public:
	static void StaticInit();
};
