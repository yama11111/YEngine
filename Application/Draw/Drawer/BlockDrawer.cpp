#include "BlockDrawer.h"

using YGame::BlockDrawer;
using YGame::Model;

void BlockDrawer::Initialize(Transform* pParent)
{
	// オブジェクト初期化
	IDrawer::Initialize(pParent);

	// モデル設定
	pModel_ = Model::CreateCube("block.png");
}

void BlockDrawer::Update()
{
	// オブジェクト更新
	obj_->UpdateMatrix();
}

void BlockDrawer::Draw(const DrawLocation location)
{
	// 描画
	pModel_->SetDrawCommand(obj_.get(), location);
}

void BlockDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}
