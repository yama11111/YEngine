#include "GridDrawer.h"

using YGame::GridDrawer;
using YGame::Model;

void GridDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, location);

	// モデル設定
	pModel_ = Model::LoadObj("grid", true);
}

void GridDrawer::Update()
{
	// オブジェクト更新
	obj_->UpdateMatrix();
}

void GridDrawer::Draw()
{
	// 描画
	pModel_->SetDrawCommand(obj_.get(), location_, Model::ShaderType::ePhong);
}

void GridDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

GridDrawer::GridDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

GridDrawer::GridDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}
