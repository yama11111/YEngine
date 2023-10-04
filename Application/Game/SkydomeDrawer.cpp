#include "SkydomeDrawer.h"
#include "ColorConfig.h"

using YGame::SkydomeDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

Model* SkydomeDrawer::spModel_ = nullptr;

SkydomeDrawer* SkydomeDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	SkydomeDrawer* newDrawer = new SkydomeDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void SkydomeDrawer::LoadResource()
{
	// モデル設定
	spModel_ = Model::LoadObj("skydome", true);
}

void SkydomeDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	isVisibleUpdate_ = false;

	cbColor_->data_.baseColor = YGame::ColorConfig::skTurquoise[0];
	//cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);

	// モデル挿入
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelSingleColor";
}

void SkydomeDrawer::InsertAnimationTimers()
{
}

void SkydomeDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
}

void SkydomeDrawer::UpdateAnimation()
{
}