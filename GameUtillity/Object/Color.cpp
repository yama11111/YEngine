#include "Color.h"
#include "MathUtillity.h"

using YGame::Color;
using YMath::Vector4;
using YMath::Vector3;
using YMath::Clamp;

Color* Color::Create(const Vector4& color, const Vector4& originalColorRate, const bool isMutable)
{
	// �C���X�^���X���� (���I)
	Color* instance = new Color();

	// �萔�o�b�t�@����
	instance->cBuff_.Create(isMutable);

	// ������
	instance->Initialize(color, originalColorRate);

	// �C���X�^���X��Ԃ�
	return instance;
}

void Color::Initialize(const Vector4& color, const Vector4& originalRate)
{
	SetRGBA(color);
	SetOriginalRateRGBA(originalRate);
}

void Color::SetDrawCommand(const UINT rootParamIndex)
{
	// �萔�o�b�t�@�ɐݒ�
	cBuff_.map_->color_ = color_;
	cBuff_.map_->originalRate_ = originalRate_;

	// �V�F�[�_�[�ɑ���
	cBuff_.SetDrawCommand(rootParamIndex);
}


void Color::SetRGBA(const Vector4& color)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float r = Clamp<float>(color.r_, 0.0f, 1.0f);
	float g = Clamp<float>(color.g_, 0.0f, 1.0f);
	float b = Clamp<float>(color.b_, 0.0f, 1.0f);
	float a = Clamp<float>(color.a_, 0.0f, 1.0f);

	// �萔�o�b�t�@���Ƒ��
	cBuff_.map_->color_ = color_ = Vector4(r, g, b, a);
}

void Color::SetRGBA(const UINT R, const UINT G, const UINT B, const UINT A)
{
	// �l�� float ��
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	float a = A <= 255 ? A / 255.0f : 1.0f;
	Vector4 c = Vector4(r, g, b, a);

	SetRGBA(c);
}

void Color::SetRGB(const Vector3& color)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	Vector4 c = { color.x_, color.y_, color.z_, color_.a_ };

	// �萔�o�b�t�@���Ƒ��
	cBuff_.map_->color_ = color_ = c;
}

void Color::SetRGB(const UINT R, const UINT G, const UINT B)
{
	// �l�� float ��
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	Vector3 c = Vector3(r, g, b);

	SetRGB(c);
}

void Color::SetAlpha(const float alpha)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float a = Clamp<float>(alpha, 0.0f, 1.0f);

	// �萔�o�b�t�@���Ƒ��
	cBuff_.map_->color_.a_ = color_.a_ = a;
}

void Color::SetAlpha(const UINT alpha)
{
	// �l�� float ��
	float a = alpha <= 255 ? alpha / 255.0f : 1.0f;

	SetAlpha(a);
}


void Color::SetOriginalRateRGBA(const Vector4& color)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float r = Clamp<float>(color.r_, 0.0f, 1.0f);
	float g = Clamp<float>(color.g_, 0.0f, 1.0f);
	float b = Clamp<float>(color.b_, 0.0f, 1.0f);
	float a = Clamp<float>(color.a_, 0.0f, 1.0f);

	// �萔�o�b�t�@���Ƒ��
	cBuff_.map_->originalRate_ = originalRate_ = Vector4(r, g, b, a);
}

void Color::SetOriginalRateRGBA(const UINT R, const UINT G, const UINT B, const UINT A)
{
	// �l�� float ��
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	float a = A <= 255 ? A / 255.0f : 1.0f;
	Vector4 c = Vector4(r, g, b, a);

	SetOriginalRateRGBA(c);
}

void Color::SetOriginalRateRGB(const Vector3& color)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	Vector4 c = { color.x_, color.y_, color.z_, color_.a_ };

	// �萔�o�b�t�@���Ƒ��
	cBuff_.map_->originalRate_ = originalRate_ = c;
}

void Color::SetOriginalRateRGB(const UINT R, const UINT G, const UINT B)
{
	// �l�� float ��
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	Vector3 c = Vector3(r, g, b);

	SetOriginalRateRGB(c);
}

void Color::SetOriginalRateAlpha(const float alpha)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float a = Clamp<float>(alpha, 0.0f, 1.0f);

	// �萔�o�b�t�@���Ƒ��
	cBuff_.map_->originalRate_.a_ = originalRate_.a_ = a;
}

void Color::SetOriginalRateAlpha(const UINT alpha)
{
	// �l�� float ��
	float a = alpha <= 255 ? alpha / 255.0f : 1.0f;

	SetOriginalRateAlpha(a);
}