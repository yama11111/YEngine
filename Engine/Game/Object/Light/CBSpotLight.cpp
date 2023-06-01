#include "CBSpotLight.h"
#include "MathUtillity.h"

#pragma region –¼‘O‹óŠÔ

using YGame::SpotLight;
using YMath::Vector3;
using YMath::Vector2;
using YMath::Clamp;

#pragma endregion

void SpotLight::Initialize(
	const Vector3& pos, 
	const Vector3& direction, 
	const Vector3& color, 
	const Vector3& atten, 
	const float startFactorAngleCos, 
	const float endFactorAngleCos)
{
	SetPos(pos);
	SetDirection(direction);
	SetColor(color);
	SetAtten(atten);
	SetStartFactorAngleCos(startFactorAngleCos);
	SetEndFactorAngleCos(endFactorAngleCos);
	isAct_ = false;
}

SpotLight::Data SpotLight::GetData() const
{
	// –ß‚è’l—p
	Data result{};

	// ‘ã“ü
	result.lightPos_ = pos_;
	result.lightVec_ = direction_;
	result.lightColor_ = color_;
	result.lightAtten_ = atten_;
	result.lightStartFactorAngleCos_ = startFactorAngleCos_;
	result.lightEndFactorAngleCos_ = endFactorAngleCos_;
	result.active_ = isAct_;

	// •Ô‚·
	return result;
}

void SpotLight::SetPos(const Vector3& pos)
{
	pos_ = pos;
}
void SpotLight::SetDirection(const Vector3& direciton)
{
	direction_ = direciton.Normalized();
}
void SpotLight::SetColor(const Vector3& color)
{
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	color_ = Vector3(r, g, b);
}
void SpotLight::SetAtten(const Vector3& atten)
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
