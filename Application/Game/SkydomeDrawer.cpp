#include "SkydomeDrawer.h"

using YGame::SkydomeDrawer;
using YGame::Model;

using YMath::Vector3;

Model* SkydomeDrawer::spModel_ = nullptr;

void SkydomeDrawer::Initialize(Transform* pParent, const uint32_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	isVisibleUpdate_ = false;

	cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);

	// モデル挿入
	obj_->SetGraphic(spModel_);

	shaderKey_ = "ModelPhong";
}

void SkydomeDrawer::Update()
{
	BaseDrawer::Update();
}

void SkydomeDrawer::Draw()
{
	BaseDrawer::Draw();
}

void SkydomeDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{

}

SkydomeDrawer::SkydomeDrawer(const uint32_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

SkydomeDrawer::SkydomeDrawer(Transform* pParent, const uint32_t drawPriority)
{
	Initialize(pParent, drawPriority);
}


void SkydomeDrawer::StaticInitialize()
{
	// モデル設定
	spModel_ = Model::LoadObj("skydome", true);
}