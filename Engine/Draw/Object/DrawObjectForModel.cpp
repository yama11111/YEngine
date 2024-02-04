#include "DrawObjectForModel.h"
#include "GraphicType.h"
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

	// ペアレント解除
	SetParent(nullptr);

	// 定数バッファが生成されてない時
	// 生成 + 挿入
	if (cbTransform_ == nullptr)
	{
		cbTransform_.reset(ConstBufferObject<CBModelTransform>::Create(isClearWhenTransition));
		InsertConstBuffer(cbTransform_.get());
	}

	// デフォルトで設定
	InsertDefaultConstBuffer(CBColor::Tag());
	InsertDefaultConstBuffer(CBMaterial::Tag());
	InsertDefaultConstBuffer(CBTexConfig::Tag());

	isVisible_ = true;
}
	

void DrawObjectForModel::Update(const Transform::Status& status)
{
	assert(pVP_);
	assert(cbTransform_);

	transform_.UpdateMatrix(status);

	cbTransform_->data_.matWorld = transform_.m;
	cbTransform_->data_.matViewProj = pVP_->view_ * pVP_->pro_;
	cbTransform_->data_.cameraPos = pVP_->eye_;
}

void DrawObjectForModel::SetViewProjection(ViewProjection* pVP)
{
	pVP_ = pVP;
}

void DrawObjectForModel::SetModel(Model* pModel)
{
	SetGraphic(pModel);
}

void DrawObjectForModel::SetGraphic(BaseGraphic* pGraphic)
{
	// null ならデフォルト
	if (pGraphic == nullptr)
	{
		pGraphic_ = DefaultGraphic::Ptr(GraphicType::kModelTag);

		return;
	}
	
	assert(GraphicType::kModelTag == pGraphic->TypeTag());

	pGraphic_ = pGraphic;
}
