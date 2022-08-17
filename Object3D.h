#pragma once
#include "Model.h"

class Object3D
{
public:
	MatWorld mW;
	Model* model;
public:
	Object3D();
	Object3D(Model* pModel);
	void SetModel(Model* pModel);
	void Update();
	void Draw(MatViewProjection& mVP, const UINT tex);
};
