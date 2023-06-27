#include "SlimeDrawer.h"

using YGame::SlimeDrawer;
using YGame::Model;

void SlimeDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, location);

	// モデル設定
	pModel_ = Model::CreateCube("enemy.png");
}

void SlimeDrawer::Update()
{
	// オブジェクト更新
	obj_->UpdateMatrix();
}

void SlimeDrawer::Draw()
{
	// 描画
	pModel_->SetDrawCommand(obj_.get(), location_);
}

void SlimeDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

SlimeDrawer::SlimeDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

SlimeDrawer::SlimeDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}
