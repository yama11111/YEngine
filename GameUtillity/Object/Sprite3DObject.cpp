#include "Sprite3DObject.h"
#include <cassert>
#include <memory>

#pragma region 名前空間

using YGame::Sprite3DObject;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

#pragma endregion

#pragma region Sprite3D

Sprite3DObject* Sprite3DObject::Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard, const bool isMutable)
{
	// インスタンスを返す
	return Create(status, isXAxisBillboard, isYAxisBillboard, nullptr, nullptr, isMutable);
}

Sprite3DObject* Sprite3DObject::Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard,
	ViewProjection* pVP, Color* pColor, const bool isMutable)
{
	// インスタンス生成 (動的)
	Sprite3DObject* instance = new Sprite3DObject();

	// 定数バッファ生成
	instance->cBuff_.Create(isMutable);

	// 初期化(デフォルト)
	instance->Initialize(status);
	instance->SetViewProjection(pVP);
	instance->SetColor(pColor);

	// インスタンスを返す
	return instance;
}

Matrix4 Sprite3DObject::BillboardMatrix()
{
	// どちらも false なら
	if (isXAxisBillboard_ == false && isYAxisBillboard_ == false)
	{
		// 単位行列を返す
		return Matrix4::Identity();
	}

	// ビルボード行列の計算
	Vector3 axisZ = (pVP_->target_ - pVP_->eye_).Normalized();
	Vector3 axisX = (pVP_->up_.Cross(axisZ)).Normalized();
	Vector3 axisY = axisZ.Cross(axisX);

	// Y軸周りビルボードなら
	if (isYAxisBillboard_)
	{
		axisY = { 0,1,0 };
		axisZ = axisX.Cross(axisY);
	}

	// ビルボード行列
	Matrix4 matBillboard(
		axisX.x_, axisX.y_, axisX.z_, 0.0f,
		axisY.x_, axisY.y_, axisY.z_, 0.0f,
		axisZ.x_, axisZ.y_, axisZ.z_, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	// ビルボード行列を返す
	return matBillboard;
}

void Sprite3DObject::SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex)
{
	// シェーダーに定数バッファ(行列)を送る
	cBuff_.map_->matWorld_ = m_ * pVP_->view_ * pVP_->pro_;
	cBuff_.map_->matBill_ = BillboardMatrix();
	cBuff_.SetDrawCommand(transformRPIndex);

	// シェーダーに定数バッファ(色)を送る
	pColor_->SetDrawCommand(colorRPIndex);
}

void Sprite3DObject::SetViewProjection(ViewProjection* pVP)
{
	// nullなら
	if (pVP == nullptr)
	{
		// デフォルト代入
		pVP_ = Default::sVP_.get();
		return;
	}

	// 代入
	pVP_ = pVP;
}
void Sprite3DObject::SetColor(Color* pColor)
{
	// nullなら
	if (pColor == nullptr)
	{
		// デフォルト代入
		pColor_ = Default::sColor_.get();
		return;
	}

	// 代入
	pColor_ = pColor;
}
void Sprite3DObject::SetIsBillboard(bool isXAxisBillboard, bool isYAxisBillboard)
{
	isXAxisBillboard_ = isXAxisBillboard;
	isYAxisBillboard_ = isYAxisBillboard;
}

#pragma endregion

#pragma region Default

std::unique_ptr<YGame::ViewProjection> Sprite3DObject::Default::sVP_ = nullptr;
std::unique_ptr<YGame::Color> Sprite3DObject::Default::sColor_ = nullptr;

void Sprite3DObject::Default::StaticInitialize()
{
	// 生成
	sVP_.reset(new YGame::ViewProjection());
	sVP_->Initialize({});

	sColor_.reset(Color::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));
}

#pragma endregion
