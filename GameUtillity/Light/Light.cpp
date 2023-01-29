#include "Light.h"
#include "MathUtillity.h"

using YGame::Light;
using YMath::Vec3;
using YMath::Clamp;

Light::Light() :
	direction_(+1.0f, +1.0f, +1.0f),
	color_(1.0f, 1.0f, 1.0f)
{
	cBuff_.Create();
	Initialize(direction_, color_);
}

void Light::Initialize(const YMath::Vec3& direction, const YMath::Vec3& color)
{
	SetDirection(direction);
	SetColor(color);
}

void Light::SetDrawCommand(const UINT rootParamIndex)
{
	cBuff_.map_->lightVec_ = direction_;
	cBuff_.map_->lightColor_ = color_;
	cBuff_.SetDrawCommand(rootParamIndex);
}

void Light::SetDirection(const YMath::Vec3& direciton)
{
	direction_ = direciton.Normalized();
}

void Light::SetColor(const YMath::Vec3& color)
{
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	cBuff_.map_->lightColor_ = Vec3(r, g, b);
}

void Light::SetColor(const UINT R, const UINT G, const UINT B)
{
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	Vec3 c = Vec3(r, g, b);

	SetColor(c);
}