#include "StageDrawer.h"
#include "SkydomeDrawer.h"

using YGame::StageDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

Model* StageDrawer::spModel_ = nullptr;

StageDrawer* StageDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	StageDrawer* newDrawer = new StageDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void StageDrawer::LoadResource()
{
	// モデル設定
	spModel_ = Model::LoadObj("tower/white/core", true);
}

void StageDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	isVisibleUpdate_ = false;

	cbColor_->data_.baseColor = Vector4(0.1f, 0.4f, 0.1f, 1.0f);
	cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);

	// モデル挿入
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelPhong";
}

void StageDrawer::InsertAnimationTimers()
{
}

void StageDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
}

void StageDrawer::UpdateAnimation()
{
}