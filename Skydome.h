#pragma once
#include "Model.h"

class Skydome 
{
private:
	YGame::Object obj_;
	YMath::Vec3* pPos_ = nullptr;
	YGame::Model* pModel_ = nullptr;
public:
	void Initialize(YMath::Vec3* pos, YGame::Model* model);
	void Update();
	void Draw(YGame::ViewProjection& vp);
};
