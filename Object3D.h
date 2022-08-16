#pragma once
#include "Model.h"

class Object3D
{
public:
	MatWorld mW;
	Model model;
public:
	Object3D();
	void Update();
	void Draw(MatViewProjection& mVP, const UINT tex);
};
