#include "Sprite3D.h"
#include <cassert>

using YGame::Sprite3DCommon;
using YGame::Sprite3D;
using YGame::TextureManager;
using YMath::Vec3;
using YMath::Mat4;

const UINT SprIndex	 = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::SpriteCB);
const UINT ColIndex	 = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::ColorCB);
const UINT TexIndex	 = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::TexDT);

void Sprite3D::Draw(ObjectSprite3D& obj, const ViewProjection& vp, Color& color, const UINT tex)
{
	if (isInvisible_) { return; }

	obj.cBuff_.map_->matWorld_ = obj.m_ * vp.view_ * vp.pro_;
	obj.cBuff_.map_->matBill_ = BillboardMatrix(vp);
	obj.cBuff_.SetDrawCommand(SprIndex);

	color.SetDrawCommand(ColIndex);

	pTexManager_->SetDrawCommand(TexIndex, tex);
	vt_.Draw();
}
void Sprite3D::Draw(ObjectSprite3D& obj, const ViewProjection& vp, const UINT tex)
{
	Draw(obj, vp, defColor_, tex);
}
void Sprite3D::Draw(ObjectSprite3D& obj, const ViewProjection& vp, Color& color)
{
	if (isInvisible_) { return; }

	obj.cBuff_.map_->matWorld_ = obj.m_ * vp.view_ * vp.pro_;
	obj.cBuff_.map_->matBill_ = BillboardMatrix(vp);
	obj.cBuff_.SetDrawCommand(SprIndex);

	color.SetDrawCommand(ColIndex);

	pTexManager_->SetDrawCommand(TexIndex, tex_);
	vt_.Draw();
}
void Sprite3D::Draw(ObjectSprite3D& obj, const ViewProjection& vp)
{
	Draw(obj, vp, defColor_);
}
YMath::Mat4 Sprite3D::BillboardMatrix(const ViewProjection& vp)
{
	if (isXAxisBillboard_ == false && isYAxisBillboard_ == false) 
	{
		return Mat4::Identity();
	}

	// ビルボード行列の計算
	Vec3 axisZ = (vp.target_ - vp.eye_).Normalized();
	Vec3 axisX = (vp.up_.Cross(axisZ)).Normalized();
	Vec3 axisY = axisZ.Cross(axisX);

	// Y軸周りビルボードなら
	if (isYAxisBillboard_)
	{
		axisY = { 0,1,0 };
		axisZ = axisX.Cross(axisY);
	}

	// ビルボード行列
	Mat4 matBillboard(
		axisX.x_, axisX.y_, axisX.z_, 0.0f,
		axisY.x_, axisY.y_, axisY.z_, 0.0f,
		axisZ.x_, axisZ.y_, axisZ.z_, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	return matBillboard;
}

Sprite3D* Sprite3D::Create(const Status& state, const UINT texIndex)
{
	// インスタンス
	Sprite3D* instance = new Sprite3D();
	instance->vt_.Initialize({{}});
	instance->tex_ = texIndex;
	instance->isXAxisBillboard_ = state.isXAxisBillboard_;
	instance->isYAxisBillboard_ = state.isYAxisBillboard_;
	instance->isInvisible_  = false;

	return instance;
}