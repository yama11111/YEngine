#include "Color.h"
#include "MathUtillity.h"

using YGame::Color;
using YMath::Vector4;
using YMath::Vector3;
using YMath::Clamp;

Color::Color() :
	color_(1.0f, 1.0f, 1.0f, 1.0f)
{}

Color* Color::Create(const YMath::Vector4& color)
{
	Color* instance = new Color();
	instance->cBuff_.Create();
	instance->Initialize(color);

	return instance;
}

void Color::Initialize(const YMath::Vector4& color)
{
	SetRGBA(color);
}

void Color::SetDrawCommand(const UINT rootParamIndex)
{
	// 定数バッファに設定
	cBuff_.map_->color_ = color_;
	// シェーダーに送る
	cBuff_.SetDrawCommand(rootParamIndex);
}

void Color::SetRGBA(const YMath::Vector4& color)
{
	// 0.0f ~ 1.0f の間になるように
	float r = Clamp<float>(color.r_, 0.0f, 1.0f);
	float g = Clamp<float>(color.g_, 0.0f, 1.0f);
	float b = Clamp<float>(color.b_, 0.0f, 1.0f);
	float a = Clamp<float>(color.a_, 0.0f, 1.0f);

	// 定数バッファに設定
	cBuff_.map_->color_ = color_ = Vector4(r, g, b, a);
}

void Color::SetRGBA(const UINT R, const UINT G, const UINT B, const UINT A)
{
	// 値を float に
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	float a = A <= 255 ? A / 255.0f : 1.0f;
	Vector4 c = Vector4(r, g, b, a);

	SetRGBA(c);
}

void Color::SetRGB(const YMath::Vector3& color)
{
	// 0.0f ~ 1.0f の間になるように
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	Vector4 c = { color.x_, color.y_, color.z_, color_.a_ };

	// 定数バッファに設定
	cBuff_.map_->color_ = color_ = c;
}

void Color::SetRGB(const UINT R, const UINT G, const UINT B)
{
	// 値を float に
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	Vector3 c = Vector3(r, g, b);

	SetRGB(c);
}

void Color::SetAlpha(const float alpha)
{
	// 0.0f ~ 1.0f の間になるように
	float a = Clamp<float>(alpha, 0.0f, 1.0f);
	
	// 定数バッファに設定
	cBuff_.map_->color_.a_ = color_.a_ = a;

}

void Color::SetAlpha(const UINT alpha)
{
	// 値を float に
	float a = alpha <= 255 ? alpha / 255.0f : 1.0f;

	SetAlpha(a);
}
