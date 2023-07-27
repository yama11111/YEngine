#include "DrawObjectForModel.h"
#include "MathVector.h"
#include <cassert>

#include "CBColor.h"
#include "CBLightGroup.h"
#include "CBMaterial.h"
#include "CBTexConfig.h"

#include "DefaultGraphic.h"

using YGame::DrawObjectForModel;

DrawObjectForModel* DrawObjectForModel::Create(
	const Transform::Status& status, 
	ViewProjection* pVP, 
	Model* pModel, 
	const bool isClearWhenTransition)
{
	DrawObjectForModel* newObj = new DrawObjectForModel();

	newObj->Initialize(status, isClearWhenTransition);

	newObj->SetViewProjection(pVP);

	newObj->SetModel(pModel);

	return newObj;
}

void DrawObjectForModel::Initialize(const Transform::Status& status, const bool isClearWhenTransition)
{
	transform_.Initialize(status);

	// �y�A�����g����
	SetParent(nullptr);

	// �萔�o�b�t�@����������ĂȂ���
	// ���� + �}��
	if (cbTransform_ == nullptr)
	{
		cbTransform_.reset(ConstBufferObject<CBModelTransform>::Create(isClearWhenTransition));
		InsertConstBuffer(cbTransform_.get());
	}

	// �f�t�H���g�Őݒ�
	InsertDefaultConstBuffer(CBColor::Tag());
	InsertDefaultConstBuffer(CBLightGroup::Tag());
	InsertDefaultConstBuffer(CBMaterial::Tag());
	InsertDefaultConstBuffer(CBTexConfig::Tag());
}
	

void DrawObjectForModel::Update(const Transform::Status& status)
{
	assert(pVP_);
	assert(cbTransform_);

	transform_.UpdateMatrix(status);

	cbTransform_->data_.matWorld = transform_.m_;
	cbTransform_->data_.matViewProj = pVP_->view_ * pVP_->pro_;
	cbTransform_->data_.cameraPos = pVP_->eye_;
}

void DrawObjectForModel::SetViewProjection(ViewProjection* pVP)
{
	assert(pVP);

	pVP_ = pVP;
}

void DrawObjectForModel::SetModel(Model* pModel)
{
	// null �Ȃ�f�t�H���g
	if (pModel == nullptr)
	{
		SetGraphic(DefaultGraphic::Ptr("Model"));
		
		return;
	}

	SetGraphic(pModel);
}
