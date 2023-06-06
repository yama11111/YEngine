#include "CBDirectionalLight.h"
#include "MathUtil.h"

#pragma region –¼‘O‹óŠÔ

using YGame::CBDirectionalLight;
using YMath::Vector3;
using YMath::Clamp;

#pragma endregion

void CBDirectionalLight::Initialize(const Vector3& direction, const Vector3& color)
{
	SetDirection(direction);
	SetColor(color);
	isAct_ = false;
}

CBDirectionalLight::Data CBDirectionalLight::GetData() const
{
	// –ß‚è’l—p
	Data result{};

	// ‘ã“ü
	result.lightVec_ = direction_;
	result.lightColor_ = color_;
	result.active_ = isAct_;

	// •Ô‚·
	return result;
}

void CBDirectionalLight::SetDirection(const Vector3& direciton)
{
	direction_ = direciton.Normalized();
}

void CBDirectionalLight::SetColor(const Vector3& color)
{
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	color_ = Vector3(r, g, b);
}