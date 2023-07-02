#include "HorseDrawer.h"

using YGame::HorseDrawer;
using YGame::Model;

Model* HorseDrawer::spModel_ = nullptr;

void HorseDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, location);

	// モデル挿入
	pModel_ = spModel_;
}

void HorseDrawer::Update()
{
	// オブジェクト更新
	obj_->UpdateMatrix();
}

void HorseDrawer::Draw()
{
	// 描画
	pModel_->SetDrawCommand(obj_.get(), location_);
}

void HorseDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

HorseDrawer::HorseDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

HorseDrawer::HorseDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}

void HorseDrawer::StaticInitialize()
{
	// モデル設定
	spModel_ = Model::CreateCube("face.png");
}
