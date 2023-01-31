#include "PointLight.h"
#include "MathUtillity.h"

using YGame::PointLight;
using YMath::Vec3;
using YMath::Clamp;

PointLight::PointLight() :
	pos_(+1.0f, +1.0f, +1.0f),
	color_(1.0f, 1.0f, 1.0f),
	atten_(+1.0f, +1.0f, +1.0f),
	isAct_(false)
{
	Initialize(pos_, color_, atten_);
}

void PointLight::Initialize(const YMath::Vec3& pos, const YMath::Vec3& color, const YMath::Vec3& atten)
{
	SetPos(pos);
	SetColor(color);
	SetAtten(atten);
	isAct_ = false;
}

void PointLight::SetPos(const YMath::Vec3& pos)
{
	pos_ = pos;
}

void PointLight::SetColor(const YMath::Vec3& color)
{
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	color_ = Vec3(r, g, b);
}
void PointLight::SetColor(const unsigned int R, const unsigned int G, const unsigned int B)
{
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	Vec3 c = Vec3(r, g, b);

	SetColor(c);
}

void PointLight::SetAtten(const YMath::Vec3& atten)
{
	float r = Clamp<float>(atten.x_, 0.0f, 1.0f);
	float g = Clamp<float>(atten.y_, 0.0f, 1.0f);
	float b = Clamp<float>(atten.z_, 0.0f, 1.0f);

	atten_ = Vec3(r, g, b);
}
