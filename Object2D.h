#pragma once
#include "YDirectX/GPUResource/ConstBufferManager.h"
#include "MatWorld.h"

class Object2D
{
public:
	MatWorld mW;
	DX::GPUResource::ConstBufferMaterial cbM;
	DX::GPUResource::ConstBufferTransform cbT;
	MatWorld* parent = nullptr;
public:
	Object2D();
	void Update();
	void SetCommand();
	void SetParent(MatWorld* parent);
private:
	static DX::GPUResource::ConstBufferManager* cbManager;
public:
	static void StaticInit();
};
