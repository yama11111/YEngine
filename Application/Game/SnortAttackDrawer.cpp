#include "SnortAttackDrawer.h"

using YGame::SnortAttackDrawer;
using YGame::Model;

Model* SnortAttackDrawer::spModel_ = nullptr;

void SnortAttackDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	// モデル設定
	obj_->SetModel(spModel_);
}

void SnortAttackDrawer::Update()
{
	BaseDrawer::Update();
}

void SnortAttackDrawer::Draw()
{
	BaseDrawer::Draw();
}

void SnortAttackDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{
}

SnortAttackDrawer::SnortAttackDrawer(const uint16_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

SnortAttackDrawer::SnortAttackDrawer(Transform* pParent, const uint16_t drawPriority)
{
	Initialize(pParent, drawPriority);
}

void SnortAttackDrawer::StaticInitialize()
{
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}
