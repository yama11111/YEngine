#include "HorseDrawer.h"

using YGame::HorseDrawer;
using YGame::Model;

void HorseDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, location);

	// モデル設定
	pModel_ = Model::CreateCube("face.png");
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
