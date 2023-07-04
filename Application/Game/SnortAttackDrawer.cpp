#include "SnortAttackDrawer.h"

using YGame::SnortAttackDrawer;
using YGame::Model;

Model* SnortAttackDrawer::spModel_ = nullptr;

void SnortAttackDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, location);

	// モデル設定
	pModel_ = spModel_;
}

void SnortAttackDrawer::Update()
{
	obj_->UpdateMatrix();
}

void SnortAttackDrawer::Draw()
{
	BaseDrawer::Draw();
}

void SnortAttackDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{
}

SnortAttackDrawer::SnortAttackDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

SnortAttackDrawer::SnortAttackDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}

void SnortAttackDrawer::StaticInitialize()
{
	spModel_ = Model::CreateCube("white1x1.png");
}
