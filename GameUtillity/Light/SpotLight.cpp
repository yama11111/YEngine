#include "SpotLight.h"
#include "MathUtillity.h"

using YGame::SpotLight;
using YMath::Vector3;
using YMath::Vector2;
using YMath::Clamp;

SpotLight::SpotLight() :
	pos_(0.0f, 0.0f, 0.0f),
	direction_(0.0f,-1.0f, 0.0f),
	color_(1.0f, 1.0f, 1.0f),
	atten_(0.005f, 0.005f, 0.005f),
	startFactorAngleCos_(0.5f),
	endFactorAngleCos_(0.2f),
	isAct_(false)
{
	Initialize(pos_, direction_, color_, atten_, startFactorAngleCos_, endFactorAngleCos_);
}

void SpotLight::Initialize(const YMath::Vector3& pos, const YMath::Vector3& direction, 
	const YMath::Vector3& color, const YMath::Vector3& atten, const float startFactorAngleCos, const float endFactorAngleCos)
{
	SetPos(pos);
	SetDirection(direction);
	SetColor(color);
	SetAtten(atten);
	SetStartFactorAngleCos(startFactorAngleCos);
	SetEndFactorAngleCos(endFactorAngleCos);
	isAct_ = false;
}

void SpotLight::SetPos(const YMath::Vector3& pos)
{
	pos_ = pos;
}
void SpotLight::SetDirection(const YMath::Vector3& direciton)
{
	direction_ = direciton.Normalized();
}
void SpotLight::SetColor(const YMath::Vector3& color)
{
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	color_ = Vector3(r, g, b);
}
void SpotLight::SetColor(const unsigned int R, const unsigned int G, const unsigned int B)
{
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	Vector3 c = Vector3(r, g, b);

	SetColor(c);
}
void SpotLight::SetAtten(const YMath::Vector3& atten)
{
	float r = Clamp<float>(atten.x_, 0.0f, 1.0f);
	float g = Clamp<float>(atten.y_, 0.0f, 1.0f);
	float b = Clamp<float>(atten.z_, 0.0f, 1.0f);

	atten_ = Vector3(r, g, b);
}
void SpotLight::SetStartFactorAngleCos(const float startFactorAngleCos)
{
	startFactorAngleCos_ = startFactorAngleCos;
}
void SpotLight::SetEndFactorAngleCos(const float endFactorAngleCos)
{
	endFactorAngleCos_ = endFactorAngleCos;
}
