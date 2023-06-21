#include "HorseDrawer.h"

using YGame::HorseDrawer;
using YGame::Model;

void HorseDrawer::Initialize(Transform* pParent)
{
	// オブジェクト初期化
	IDrawer::Initialize(pParent);

	// モデル設定
	pModel_ = Model::CreateCube("horse.png");
}

void HorseDrawer::Update()
{
	// オブジェクト更新
	obj_->UpdateMatrix();
}

void HorseDrawer::Draw(const DrawLocation location)
{
	// 描画
	pModel_->SetDrawCommand(obj_.get(), location);
}

void HorseDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}
