#include "Skydome.h"
#include <cassert>

using YGame::Skydome;

void Skydome::Initialize(const BaseObject::Status state, YGame::Model* model)
{
	assert(model);
	pModel_ = model;

	obj_.reset(ObjectModel::Create(state));
}

void Skydome::Update()
{
	obj_->UpdateMatrix();
}

void Skydome::Draw(YGame::ViewProjection& vp, YGame::LightGroup* lightGroup)
{
	pModel_->Draw(obj_.get(), vp, lightGroup);
}