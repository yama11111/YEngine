#pragma once
#include "Model.h"

class Skydome 
{
private:
	Game::Object obj_;
	Game::Model* model_ = nullptr;
public:
	void Initialize(Game::Model* model);
	void Update();
	void Draw(Game::ViewProjection& vp);
};