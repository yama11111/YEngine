#include "SkydomeDrawer.h"

using YGame::SkydomeDrawer;
using YGame::Model;

void SkydomeDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, location);

	// モデル設定
	pModel_ = Model::LoadObj("skydome", true);
}

void SkydomeDrawer::Update()
{
	// オブジェクト更新
	obj_->UpdateMatrix();
}

void SkydomeDrawer::Draw()
{
	// 描画
	pModel_->SetDrawCommand(obj_.get(), location_);
}

void SkydomeDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

SkydomeDrawer::SkydomeDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

SkydomeDrawer::SkydomeDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}
