#include "DirectionalLight.h"
#include "MathUtillity.h"

using YGame::DirectionalLight;
using YMath::Vec3;
using YMath::Clamp;

DirectionalLight::DirectionalLight() :
	direction_(+1.0f, +1.0f, +1.0f),
	color_(1.0f, 1.0f, 1.0f),
	isAct_(false)
{
	Initialize(direction_, color_);
}

void DirectionalLight::Initialize(const YMath::Vec3& direction, const YMath::Vec3& color)
{
	SetDirection(direction);
	SetColor(color);
	isAct_ = false;
}

void DirectionalLight::SetDirection(const YMath::Vec3& direciton)
{
	direction_ = direciton.Normalized();
}

void DirectionalLight::SetColor(const YMath::Vec3& color)
{
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	color_ = Vec3(r, g, b);
}
void DirectionalLight::SetColor(const unsigned int R, const unsigned int G, const unsigned int B)
{
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	Vec3 c = Vec3(r, g, b);

	SetColor(c);
}