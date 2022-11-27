#include "Skydome.h"
#include <cassert>

const float Size = 300.0f;

void Skydome::Initialize(Game::Model* model)
{
	assert(model);
	pModel_ = model;
	obj_.Initialize({});
	obj_.scale_ = { Size, Size, Size };
	Update();
}

void Skydome::Update()
{
	obj_.Update();
}

void Skydome::Draw(Game::ViewProjection& vp)
{
	pModel_->Draw(obj_, vp);
}