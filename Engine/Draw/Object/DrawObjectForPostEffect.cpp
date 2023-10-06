#include "DrawObjectForPostEffect.h"
#include "MathVector.h"
#include <cassert>

#include "CBColor.h"
#include "CBTexConfig.h"

#include "DefaultGraphic.h"

using YGame::DrawObjectForPostEffect;

DrawObjectForPostEffect* DrawObjectForPostEffect::Create(
	const Transform::Status& status, 
	PostEffect* pPostEffect, 
	const bool isClearWhenTransition)
{
	DrawObjectForPostEffect* newObj = new DrawObjectForPostEffect();

	newObj->Initialize(status, isClearWhenTransition);

	newObj->SetPostEffect(pPostEffect);

	return newObj;
}

void DrawObjectForPostEffect::Initialize(const Transform::Status& status, const bool isClearWhenTransition)
{
	transform_.Initialize(status);

	// ペアレント解除
	SetParent(nullptr);

	// 定数バッファが生成されてない時
	// 生成 + 挿入
	if (cbTransform_ == nullptr)
	{
		cbTransform_.reset(ConstBufferObject<CBPostEffectTransform>::Create(isClearWhenTransition));
		InsertConstBuffer(cbTransform_.get());
	}

	// デフォルトで設定
	InsertDefaultConstBuffer(CBColor::Tag());
	InsertDefaultConstBuffer(CBTexConfig::Tag());

	isVisible_ = true;
}

void DrawObjectForPostEffect::Update(const Transform::Status& status)
{
	assert(cbTransform_);

	transform_.UpdateMatrix(status);

	cbTransform_->data_.matWorld = transform_.m_ * YMath::MatOrthoGraphic();
}

void DrawObjectForPostEffect::SetPostEffect(PostEffect* pPostEffect)
{
	// null ならデフォルト
	if (pPostEffect == nullptr)
	{
		SetGraphic(DefaultGraphic::Ptr("PostEffect"));

		return;
	}

	SetGraphic(pPostEffect);
}
