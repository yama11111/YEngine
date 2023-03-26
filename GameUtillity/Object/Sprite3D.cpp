#include "Sprite3D.h"
#include <cassert>

#pragma region 名前空間

using YGame::Sprite3DObject;
using YGame::Sprite3DCommon;
using YGame::Sprite3D;
using YGame::TextureManager;
using YMath::Vector3;
using YMath::Matrix4;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT TraIndex = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::TransformCB); // obj
static const UINT ColIndex = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::ColorCB); // color
static const UINT TexIndex = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::TexDT); // tex

#pragma endregion


#pragma region Sprite3DCBSet

Sprite3DObject* Sprite3DObject::Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard)
{
	// インスタンスを返す
	return Create(status, isXAxisBillboard, isYAxisBillboard, nullptr, nullptr);
}

Sprite3DObject* Sprite3DObject::Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard, 
	ViewProjection* pVP, Color* pColor)
{
	// インスタンス生成 (動的)
	Sprite3DObject* instance = new Sprite3DObject();

	// 定数バッファ生成
	instance->cBuff_.Create();

	// 初期化(デフォルト)
	instance->Initialize(status);
	instance->SetViewProjection(pVP);
	instance->SetColor(pColor);

	// インスタンスを返す
	return instance;
}

void Sprite3DObject::SetIsBillboard(bool isXAxisBillboard, bool isYAxisBillboard)
{
	isXAxisBillboard_ = isXAxisBillboard;
	isYAxisBillboard_ = isYAxisBillboard;
}
void Sprite3DObject::SetViewProjection(ViewProjection* pVP)
{
	// nullなら
	if (pVP == nullptr)
	{
		// デフォルト代入
		pVP_ = sDefVP_.get();
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
		pColor_ = sDefColor_.get();
		return;
	}

	// 代入
	pColor_ = pColor;
}

void Sprite3DObject::SetDrawCommand()
{
	// シェーダーに定数バッファ(行列)を送る
	cBuff_.map_->matWorld_ = m_ * pVP_->view_ * pVP_->pro_;
	cBuff_.map_->matBill_ = BillboardMatrix();
	cBuff_.SetDrawCommand(TraIndex);

	// シェーダーに定数バッファ(色)を送る
	pColor_->SetDrawCommand(ColIndex);
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

#pragma endregion


#pragma region Sprite3D

Sprite3D* Sprite3D::Create(const UINT texIndex)
{
	// インスタンス生成 (動的)
	Sprite3D* instance = new Sprite3D();
	
	// 初期化
	instance->vt_.Initialize({{}});
	
	// テクスチャ番号
	instance->tex_ = texIndex;

	// 描画する
	instance->isInvisible_  = false;
	
	
	// インスタンスを返す
	return instance;
}

void Sprite3D::Draw(Sprite3DObject* pObj)
{
	// 描画しないなら弾く
	if (isInvisible_) { return; }

	// 定数バッファをシェーダーに送る
	pObj->SetDrawCommand();

	// テクスチャ
	spTexManager_->SetDrawCommand(TexIndex, tex_);

	// 頂点バッファを送る + 描画コマンド
	vt_.Draw();
}

#pragma endregion