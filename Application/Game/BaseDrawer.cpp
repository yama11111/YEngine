#include "BaseDrawer.h"
#include "PipelineManager.h"
#include <cassert>

using YGame::BaseDrawer;

YGame::ViewProjection* BaseDrawer::spVP_ = nullptr;

void BaseDrawer::Initialize(Transform* pParent, const uint32_t drawPriority)
{
	transform_.reset(new Transform());

	// 親設定
	SetParent(pParent);
	
	// オブジェクト + 定数バッファ生成
	// 生成後、オブジェクトに挿入
	obj_.reset(new Object());

	cbTransform_.reset(ConstBuffer<CBModelTransform::CBData>::Create());
	obj_->InsertConstBuffer(CBModelTransform::KeyName(), cbTransform_.get());

	cbColor_.reset(ConstBuffer<CBColor::CBData>::Create());
	obj_->InsertConstBuffer(CBColor::KeyName(), cbColor_.get());

	cbMaterial_.reset(ConstBuffer<CBMaterial::CBData>::Create());
	cbMaterial_->data_.ambient = { 0.2f,0.2f,0.2f };
	obj_->InsertConstBuffer(CBMaterial::KeyName(), cbMaterial_.get());

	cbLightGroup_.reset(ConstBuffer<CBLightGroup::CBData>::Create());
	cbLightGroup_->data_.direLights[0].active = 1.0f;
	obj_->InsertConstBuffer(CBLightGroup::KeyName(), cbLightGroup_.get());

	cbTexConfig_.reset(ConstBuffer<CBTexConfig::CBData>::Create());
	obj_->InsertConstBuffer(CBTexConfig::KeyName(), cbTexConfig_.get());


	drawPriority_ = drawPriority;

	isVisible_ = true;

	isVisibleUpdate_ = true;

	animationBitFlag_ = 0;

	animeStatus_ = {};
}

void BaseDrawer::Update()
{
	transform_->UpdateMatrix(animeStatus_);

	cbTransform_->data_.matWorld = transform_->m_;
	cbTransform_->data_.matViewProj = spVP_->view_ * spVP_->pro_;
	cbTransform_->data_.cameraPos = spVP_->eye_;
}

void BaseDrawer::VisibleUpdate()
{
	if (isVisibleUpdate_ == false)
	{
		cbColor_->data_.texColorRate.a_ = 1.0f;

		return;
	}

	// 視点との距離
	float distance = YMath::Vector3(spVP_->eye_ - pParent_->pos_).Length();

	// 描画範囲
	static const float kRange = 750.0f;

	// 視点との距離の比率でアルファ値変化(遠いほど薄く)
	float distanceRate = 1.0f - distance / kRange;
	if (distanceRate >= 0.8f) { distanceRate = 1.0f; }

	cbColor_->data_.texColorRate.a_ = distanceRate;

	// 一定値以下は描画切る
	isVisible_ = (distanceRate >= 0.25f);
}

void BaseDrawer::Draw()
{
	if (isVisible_ == false) { return; }

	// パイプラインに描画を積む
	PipelineManager::GetInstance()->EnqueueDrawSet(shaderKey_, drawPriority_, obj_.get());
}

void BaseDrawer::SetParent(Transform* pParent)
{
	// 親トランスフォームポインタ設定
	pParent_ = pParent;

	// null じゃないなら
	if (pParent_)
	{
		// 親子関係設定
		transform_->parent_ = &pParent_->m_;
	}
	// 違うなら
	else
	{
		// 親子関係初期化
		transform_->parent_ = nullptr;
	}
}

void BaseDrawer::StaticInitialize(ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);

	// 代入
	spVP_ = pVP;
}

BaseDrawer::BaseDrawer(const uint32_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

BaseDrawer::BaseDrawer(Transform* pParent, const uint32_t drawPriority)
{
	Initialize(pParent, drawPriority);
}

void BaseDrawer::DrawDebugTextContent()
{

}
