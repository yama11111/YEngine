#include "DrawObjectForSprite3D.h"
#include "MathVector.h"
#include <cassert>

#include "CBColor.h"
#include "CBTexConfig.h"

#include "DefaultGraphic.h"

using YGame::DrawObjectForSprite3D;

DrawObjectForSprite3D* DrawObjectForSprite3D::Create(
	const Transform::Status& status, 
	const bool isXAxisBillboard, const bool isYAxisBillboard,
	ViewProjection* pVP, 
	Sprite3D* pSprite3D, 
	const bool isClearWhenTransition)
{
	DrawObjectForSprite3D* newObj = new DrawObjectForSprite3D();

	newObj->Initialize(status, isClearWhenTransition);

	newObj->SetBillboardFrag(isXAxisBillboard, isYAxisBillboard);

	newObj->SetViewProjection(pVP);

	newObj->SetSprite3D(pSprite3D);

	return newObj;
}

void DrawObjectForSprite3D::Initialize(const Transform::Status& status, const bool isClearWhenTransition)
{
	transform_.Initialize(status);

	// ペアレント解除
	SetParent(nullptr);

	// 定数バッファが生成されてない時
	// 生成 + 挿入
	if (cbTransform_ == nullptr)
	{
		cbTransform_.reset(ConstBufferObject<CBSprite3DTransform>::Create(isClearWhenTransition));
		InsertConstBuffer(cbTransform_.get());
	}

	// デフォルトで設定
	InsertDefaultConstBuffer(CBColor::Tag());
	InsertDefaultConstBuffer(CBTexConfig::Tag());

	isVisible_ = true;
}


void DrawObjectForSprite3D::Update(const Transform::Status& status)
{
	assert(pVP_);
	assert(cbTransform_);

	transform_.UpdateMatrix(status);

	cbTransform_->data_.matWorld = transform_.m_ * pVP_->view_ * pVP_->pro_;
	cbTransform_->data_.matBill = YMath::MatBillboard(isXAxisBillboard_, isYAxisBillboard_, pVP_->eye_, pVP_->target_, pVP_->eye_);
}

void DrawObjectForSprite3D::SetBillboardFrag(const bool isXAxisBillboard, const bool isYAxisBillboard)
{
	isXAxisBillboard_ = isXAxisBillboard;
	isYAxisBillboard_ = isYAxisBillboard;
}

void DrawObjectForSprite3D::SetViewProjection(ViewProjection* pVP)
{
	assert(pVP);

	pVP_ = pVP;
}

void DrawObjectForSprite3D::SetSprite3D(Sprite3D* pSprite3D)
{
	// null ならデフォルト
	if (pSprite3D == nullptr)
	{
		SetGraphic(DefaultGraphic::Ptr("Sprite3D"));

		return;
	}

	SetGraphic(pSprite3D);
}
