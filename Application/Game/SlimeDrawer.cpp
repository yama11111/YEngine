#include "SlimeDrawer.h"

using YGame::SlimeDrawer;

void SlimeDrawer::Initialize(Transform* pParent)
{
	// オブジェクト初期化
	IDrawer::Initialize(pParent);
	
	// モデル設定
	pModel_ = Model::CreateCube("enemy.png");
}

void SlimeDrawer::Update()
{
	// オブジェクト更新
	obj_->UpdateMatrix();
}

void SlimeDrawer::Draw(const DrawLocation location)
{
	// 描画
	pModel_->SetDrawCommand(obj_.get(), location);
}

void SlimeDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}
