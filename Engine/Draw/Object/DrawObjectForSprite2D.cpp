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

	// �y�A�����g����
	SetParent(nullptr);

	// �萔�o�b�t�@����������ĂȂ���
	// ���� + �}��
	if (cbTransform_ == nullptr)
	{
		cbTransform_.reset(ConstBufferObject<CBSprite2DTransform>::Create(isClearWhenTransition));
		InsertConstBuffer(cbTransform_.get());
	}

	// �f�t�H���g�Őݒ�
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
	// null �Ȃ�f�t�H���g
	if (pSprite2D == nullptr)
	{
		SetGraphic(DefaultGraphic::Ptr("Sprite2D"));

		return;
	}

	SetGraphic(pSprite2D);
}
