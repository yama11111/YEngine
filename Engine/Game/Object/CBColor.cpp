#include "CBColor.h"
#include "MathUtillity.h"

#pragma region 名前空間

using YGame::CBColor;
using YMath::Vector4;
using YMath::Vector3;
using YMath::Clamp;

#pragma endregion

CBColor* CBColor::Create(const Vector4& color, const Vector4& originalColorRate, const bool isMutable)
{
	// インスタンス生成 (動的)
	CBColor* instance = new CBColor();

	// 定数バッファ生成
	instance->cBuff_.Create(isMutable);

	// 初期化
	instance->Initialize(color, originalColorRate);

	// インスタンスを返す
	return instance;
}

void CBColor::Initialize(const Vector4& color, const Vector4& originalRate)
{
	SetRGBA(color);
	SetTexColorRateRGBA(originalRate);
}

void CBColor::SetDrawCommand(const UINT rootParamIndex)
{
	// 定数バッファに設定
	cBuff_.map_->baseColor_ = baseColor_;
	cBuff_.map_->texColorRate_ = texColorRate_;

	// シェーダーに送る
	cBuff_.SetDrawCommand(rootParamIndex);
}

void CBColor::SetRGBA(const Vector4& color)
{
	// 0.0f ~ 1.0f の間になるように
	float r = Clamp<float>(color.r_, 0.0f, 1.0f);
	float g = Clamp<float>(color.g_, 0.0f, 1.0f);
	float b = Clamp<float>(color.b_, 0.0f, 1.0f);
	float a = Clamp<float>(color.a_, 0.0f, 1.0f);

	// 代入
	baseColor_ = Vector4(r, g, b, a);
}

void CBColor::SetRGB(const Vector3& color)
{
	// 0.0f ~ 1.0f の間になるように
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	Vector4 c = { color.x_, color.y_, color.z_, baseColor_.a_ };

	// 代入
	baseColor_ = c;
}

void CBColor::SetAlpha(const float alpha)
{
	// 0.0f ~ 1.0f の間になるように
	float a = Clamp<float>(alpha, 0.0f, 1.0f);

	// 代入
	baseColor_.a_ = a;
}


void CBColor::SetTexColorRateRGBA(const Vector4& colorRate)
{
	// 0.0f ~ 1.0f の間になるように
	float r = Clamp<float>(colorRate.r_, 0.0f, 1.0f);
	float g = Clamp<float>(colorRate.g_, 0.0f, 1.0f);
	float b = Clamp<float>(colorRate.b_, 0.0f, 1.0f);
	float a = Clamp<float>(colorRate.a_, 0.0f, 1.0f);

	// 代入
	texColorRate_ = Vector4(r, g, b, a);
}

void CBColor::SetTexColorRateRGB(const Vector3& colorRate)
{
	// 0.0f ~ 1.0f の間になるように
	float r = Clamp<float>(colorRate.x_, 0.0f, 1.0f);
	float g = Clamp<float>(colorRate.y_, 0.0f, 1.0f);
	float b = Clamp<float>(colorRate.z_, 0.0f, 1.0f);

	Vector4 c = { colorRate.x_, colorRate.y_, colorRate.z_, baseColor_.a_ };

	// 代入
	texColorRate_ = c;
}

void CBColor::SetTexColorRateAlpha(const float alphaRate)
{
	// 0.0f ~ 1.0f の間になるように
	float a = Clamp<float>(alphaRate, 0.0f, 1.0f);

	// 代入
	texColorRate_.a_ = a;
}