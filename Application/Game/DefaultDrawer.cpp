#include "DefaultDrawer.h"

using YGame::DefaultDrawer;
using YGame::Model;

void DefaultDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, location);

	// モデル設定
	pModel_ = Model::CreateCube("white1x1.png");
}

void DefaultDrawer::Update()
{
	// オブジェクト更新
	obj_->UpdateMatrix();
}

void DefaultDrawer::Draw()
{
	// 描画
	pModel_->SetDrawCommand(obj_.get(), location_, Model::ShaderType::ePhong);
}

void DefaultDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

DefaultDrawer::DefaultDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

DefaultDrawer::DefaultDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}
