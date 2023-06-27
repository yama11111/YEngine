#include "PlayerDrawer.h"

using YGame::PlayerDrawer;
using YGame::Model;

void PlayerDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, location);

	// モデル設定
	pModel_ = Model::CreateCube("player.png");
}

void PlayerDrawer::Update()
{
	// オブジェクト更新
	obj_->UpdateMatrix();
}

void PlayerDrawer::Draw()
{
	// 描画
	pModel_->SetDrawCommand(obj_.get(), location_);
}

void PlayerDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

PlayerDrawer::PlayerDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

PlayerDrawer::PlayerDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}
