#include "LightGroup.h"
#include "MathUtillity.h"
#include <cassert>

using YGame::LightGroup;
using YMath::Vec3;
using YMath::Clamp;

const std::array<Vec3, LightGroup::DireLightNum_> DefaultDirection =
{
	Vec3( 0.0f,-1.0f, 0.0f),
	Vec3(+0.5f,+0.1f,+0.2f),
	Vec3(-0.5f,+0.1f,-0.2f),
};

LightGroup::LightGroup() :
	ambientColor_(1.0f, 1.0f, 1.0f),
	direLights_()
{}

LightGroup* LightGroup::Create()
{
	LightGroup* instance = new LightGroup();
	instance->cBuff_.Create();
	instance->Initialize();

	return instance;
}

void LightGroup::Initialize(const YMath::Vec3& ambientColor)
{
	SetAmbientColor(ambientColor);
	for (size_t i = 0; i < DireLightNum_; i++)
	{
		direLights_[i].Initialize(DefaultDirection[i]);
		direLights_[i].SetActive(true);
	}
}

void LightGroup::SetDrawCommand(const UINT rootParamIndex)
{
	cBuff_.map_->ambientColor_ = ambientColor_;
	for (size_t i = 0; i < DireLightNum_; i++)
	{
		if (direLights_[i].IsActive())
		{
			cBuff_.map_->direLights_[i].lightVec_ = direLights_[i].Direction();
			cBuff_.map_->direLights_[i].lightColor_ = direLights_[i].Color();
			cBuff_.map_->direLights_[i].active_ = 1;
		}
		else
		{
			cBuff_.map_->direLights_[i].active_ = 0;
		}
	}

	cBuff_.SetDrawCommand(rootParamIndex);
}

void LightGroup::SetAmbientColor(const YMath::Vec3& color)
{
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	cBuff_.map_->ambientColor_ = ambientColor_ = Vec3(r, g, b);
}
void LightGroup::SetAmbientColor(const UINT R, const UINT G, const UINT B)
{
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	Vec3 c = Vec3(r, g, b);

	SetAmbientColor(c);
}

void LightGroup::SetDirectionalLightDirection(const size_t index, const YMath::Vec3& direction)
{
	assert(index < DireLightNum_);
	direLights_[index].SetDirection(direction);
}
void LightGroup::SetDirectionalLightColor(const size_t index, const YMath::Vec3& color)
{
	assert(index < DireLightNum_);
	direLights_[index].SetColor(color);
}
void LightGroup::SetDirectionalLightActive(const size_t index, const bool isAct)
{
	assert(index < DireLightNum_);
	direLights_[index].SetActive(isAct);
}