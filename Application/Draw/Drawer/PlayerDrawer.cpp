#include "PlayerDrawer.h"

using YGame::PlayerDrawer;
using YGame::Model;

void PlayerDrawer::Initialize(Transform* pParent)
{
	// オブジェクト初期化
	IDrawer::Initialize(pParent);
	
	// モデル設定
	pModel_ = Model::CreateCube("player.png");
}

void PlayerDrawer::Update()
{
	// オブジェクト更新
	obj_->UpdateMatrix();
}

void PlayerDrawer::Draw(const DrawLocation location)
{
	// 描画
	pModel_->SetDrawCommand(obj_.get(), location);
}

void PlayerDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}
