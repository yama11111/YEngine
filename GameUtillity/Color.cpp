#include "Color.h"
#include "MathUtillity.h"

using YGame::Color;
using YMath::Vec4;
using YMath::Clamp;

Color::Color() :
	color_(1.0f, 1.0f, 1.0f, 1.0f)
{
	cBuff_.Create();
	Initialize();
}

void Color::Initialize(const YMath::Vec4& color)
{
	SetRGBA(color);
}

void Color::SetDrawCommand(const UINT rootParamIndex)
{
	cBuff_.SetDrawCommand(rootParamIndex);
}

void Color::SetRGBA(const YMath::Vec4& color)
{
	float r = Clamp<float>(color.r_, 0.0f, 1.0f);
	float g = Clamp<float>(color.g_, 0.0f, 1.0f);
	float b = Clamp<float>(color.b_, 0.0f, 1.0f);
	float a = Clamp<float>(color.a_, 0.0f, 1.0f);
	Vec4 c = Vec4(r, g, b, a);

	cBuff_.map_->color_ = color;
}

void Color::SetRGBA(const UINT R, const UINT G, const UINT B, const UINT A)
{
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	float a = A <= 255 ? A / 255.0f : 1.0f;
	Vec4 c = Vec4(r, g, b, a);

	SetRGBA(c);
}
