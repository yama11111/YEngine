#include "BlockDrawer.h"

using YGame::BlockDrawer;
using YGame::Model;

void BlockDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, location);

	// モデル設定
	pModel_ = Model::CreateCube("block.png");
}

void BlockDrawer::Update()
{
	// オブジェクト更新
	obj_->UpdateMatrix();
}

void BlockDrawer::Draw()
{
	// 描画
	pModel_->SetDrawCommand(obj_.get(), location_);
}

void BlockDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

BlockDrawer::BlockDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

BlockDrawer::BlockDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}
