#include "Sprite3D.h"

#pragma region 名前空間

using YGame::Sprite3DCommon;
using YGame::Sprite3D;
using YGame::ObjectSprite3D;
using YGame::TextureManager;
using YMath::Vector3;
using YMath::Matrix4;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT ObjIndex = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::ObjCB); // obj
static const UINT ColIndex = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::ColorCB); // color
static const UINT TexIndex = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::TexDT); // tex

#pragma endregion

ObjectSprite3D* ObjectSprite3D::Create(const Status& state)
{
	// インスタンス生成 (動的)
	ObjectSprite3D* instance = new ObjectSprite3D();

	// 定数バッファ生成
	instance->cBuff_.Create();
	// 初期化
	instance->Initialize(state);

	// インスタンスを返す
	return instance;
}

void Sprite3D::Draw(ObjectSprite3D* pObj, const ViewProjection& vp, Color* pColor, const UINT tex)
{
	// 描画しないなら弾く
	if (isInvisible_) { return; }

	// シェーダーに定数バッファ(行列)を送る
	pObj->cBuff_.map_->matWorld_ = pObj->m_ * vp.view_ * vp.pro_;
	pObj->cBuff_.map_->matBill_ = BillboardMatrix(vp);
	pObj->cBuff_.SetDrawCommand(ObjIndex);

	// シェーダーに定数バッファ(色)を送る
	pColor->SetDrawCommand(ColIndex);

	// シェーダーにテクスチャを送る
	pTexManager_->SetDrawCommand(TexIndex, tex);
	
	// シェーダーに頂点バッファを送る + 描画コマンド
	vt_.Draw();
}
void Sprite3D::Draw(ObjectSprite3D* pObj, const ViewProjection& vp, const UINT tex)
{
	// デフォルトの色を渡して描画
	Draw(pObj, vp, defColor_.get(), tex);
}
void Sprite3D::Draw(ObjectSprite3D* pObj, const ViewProjection& vp, Color* pColor)
{
	// 描画しないなら弾く
	if (isInvisible_) { return; }

	// シェーダーに定数バッファ(行列)を送る
	pObj->cBuff_.map_->matWorld_ = pObj->m_ * vp.view_ * vp.pro_;
	pObj->cBuff_.map_->matBill_ = BillboardMatrix(vp);
	pObj->cBuff_.SetDrawCommand(ObjIndex);

	// シェーダーに定数バッファ(色)を送る
	pColor->SetDrawCommand(ColIndex);

	// シェーダーにテクスチャを送る
	pTexManager_->SetDrawCommand(TexIndex, tex_);
	
	// シェーダーに頂点バッファを送る + 描画コマンド
	vt_.Draw();
}
void Sprite3D::Draw(ObjectSprite3D* pObj, const ViewProjection& vp)
{
	// デフォルトの色を渡して描画
	Draw(pObj, vp, defColor_.get());
}
YMath::Matrix4 Sprite3D::BillboardMatrix(const ViewProjection& vp)
{
	// どちらも false なら
	if (isXAxisBillboard_ == false && isYAxisBillboard_ == false) 
	{
		// 単位行列を返す
		return Matrix4::Identity();
	}

	// ビルボード行列の計算
	Vector3 axisZ = (vp.target_ - vp.eye_).Normalized();
	Vector3 axisX = (vp.up_.Cross(axisZ)).Normalized();
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

Sprite3D* Sprite3D::Create(const Status& state, const UINT texIndex)
{
	// インスタンス生成 (動的)
	Sprite3D* instance = new Sprite3D();
	
	// 初期化
	instance->vt_.Initialize({{}});
	
	//  色 (そのまま)
	instance->defColor_.reset(Color::Create());
	
	// ビルボードか
	instance->isXAxisBillboard_ = state.isXAxisBillboard_; // X軸
	instance->isYAxisBillboard_ = state.isYAxisBillboard_; // Y軸
	
	// テクスチャ番号
	instance->tex_ = texIndex;

	// 描画する
	instance->isInvisible_  = false;
	
	
	// インスタンスを返す
	return instance;
}
