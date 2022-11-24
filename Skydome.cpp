#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Game::Model* model)
{
	assert(model);
	model_ = model;
	obj_.Initialize({});
	obj_.scale_ = { 150.0f, 150.0f, 150.0f };
	Update();
}

void Skydome::Update()
{
	obj_.Update();
}

void Skydome::Draw(Game::ViewProjection& vp)
{
	model_->Draw(obj_, vp);
}