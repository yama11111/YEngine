#include "Skydome.h"
#include <cassert>

const float Size = 600.0f;
const float Rotate = 3.141592f * 0.0005f;

void Skydome::Initialize(YMath::Vec3* pos, YGame::Model* model)
{
	assert(model);
	assert(pos);

	pPos_ = pos;
	pModel_ = model;
	obj_.Initialize({});
	obj_.scale_ = { Size, Size, Size };
	Update();
}

void Skydome::Update()
{
	obj_.pos_ = YMath::Vec3(0.0f, -20.0f, pPos_->z_);
	obj_.rota_.y_ -= Rotate;
	obj_.UpdateMatrix();
}

void Skydome::Draw(YGame::ViewProjection& vp, YGame::LightGroup* lightGroup)
{
	pModel_->Draw(obj_, vp, lightGroup);
}