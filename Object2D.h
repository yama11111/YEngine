#pragma once
#include "ConstBufferManager.h"
#include "MatWorld.h"

class Object2D
{
public:
	MatWorld mW;
	ConstBufferMaterial cbM;
	ConstBufferTransform cbT;
	MatWorld* parent = nullptr;
public:
	Object2D();
	void Update();
	void SetCommand();
	void SetParent(MatWorld* parent);
private:
	static ConstBufferManager* cbManager;
public:
	static void StaticInit();
};
