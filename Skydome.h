#pragma once
#include "Model.h"

class Skydome 
{
private:
	YGame::Object obj_;
	YGame::Model* pModel_ = nullptr;
public:
	void Initialize(YGame::Model* model);
	void Update();
	void Draw(YGame::ViewProjection& vp);
};
