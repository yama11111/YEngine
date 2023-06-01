#include "CBPointLight.h"
#include "MathUtillity.h"

#pragma region –¼‘O‹óŠÔ

using YGame::CBPointLight;
using YMath::Vector3;
using YMath::Clamp;

#pragma endregion

void CBPointLight::Initialize(const Vector3& pos, const Vector3& color, const Vector3& atten)
{
	SetPos(pos);
	SetColor(color);
	SetAtten(atten);
	isAct_ = false;
}

CBPointLight::Data CBPointLight::GetData() const
{
	// –ß‚è’l—p
	Data result{};

	// ‘ã“ü
	result.lightPos_ = pos_;
	result.lightColor_ = color_;
	result.lightAtten_ = atten_;
	result.active_ = isAct_;

	// •Ô‚·
	return result;
}

void CBPointLight::SetPos(const Vector3& pos)
{
	pos_ = pos;
}
void CBPointLight::SetColor(const Vector3& color)
{
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	color_ = Vector3(r, g, b);
}
void CBPointLight::SetColor(const unsigned int R, const unsigned int G, const unsigned int B)
{
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	Vector3 c = Vector3(r, g, b);

	SetColor(c);
}
void CBPointLight::SetAtten(const Vector3& atten)
{
	float r = Clamp<float>(atten.x_, 0.0f, 1.0f);
	float g = Clamp<float>(atten.y_, 0.0f, 1.0f);
	float b = Clamp<float>(atten.z_, 0.0f, 1.0f);

	atten_ = Vector3(r, g, b);
}
