#include "DrawObjectForSprite2D.h"
#include "MathVector.h"
#include <cassert>

#include "CBColor.h"
#include "CBTexConfig.h"

#include "DefaultGraphic.h"

using YGame::DrawObjectForSprite2D;

DrawObjectForSprite2D* DrawObjectForSprite2D::Create(
	const Transform::Status& status, 
	Sprite2D* pSprite2D, 
	const bool isClearWhenTransition)
{
	DrawObjectForSprite2D* newObj = new DrawObjectForSprite2D();

	newObj->Initialize(status, isClearWhenTransition);

	newObj->SetSprite2D(pSprite2D);

	return newObj;
}

void DrawObjectForSprite2D::Initialize(const Transform::Status& status, const bool isClearWhenTransition)
{
	transform_.Initialize(status);

	// ペアレント解除
	SetParent(nullptr);

	// 定数バッファが生成されてない時
	// 生成 + 挿入
	if (cbTransform_ == nullptr)
	{
		cbTransform_.reset(ConstBufferObject<CBSprite2DTransform>::Create(isClearWhenTransition));
		InsertConstBuffer(cbTransform_.get());
	}

	// デフォルトで設定
	InsertDefaultConstBuffer(CBColor::Tag());
	InsertDefaultConstBuffer(CBTexConfig::Tag());
}

void DrawObjectForSprite2D::Update(const Transform::Status& status)
{
	assert(cbTransform_);

	transform_.UpdateMatrix(status);

	cbTransform_->data_.matWorld = transform_.m_ * YMath::MatOrthoGraphic();
}

void DrawObjectForSprite2D::SetSprite2D(Sprite2D* pSprite2D)
{
	// null ならデフォルト
	if (pSprite2D == nullptr)
	{
		SetGraphic(DefaultGraphic::Ptr("Sprite2D"));

		return;
	}

	SetGraphic(pSprite2D);
}
