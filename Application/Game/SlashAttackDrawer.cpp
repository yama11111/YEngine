#include "SlashAttackDrawer.h"

using YGame::SlashAttackDrawer;
using YGame::Model;

Model* SlashAttackDrawer::spModel_ = nullptr;

void SlashAttackDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	// モデル設定
	obj_->SetModel(spModel_);
}

void SlashAttackDrawer::Update()
{
	BaseDrawer::Update();
}

void SlashAttackDrawer::Draw()
{
	BaseDrawer::Draw();
}

void SlashAttackDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{
}

SlashAttackDrawer::SlashAttackDrawer(const uint16_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

SlashAttackDrawer::SlashAttackDrawer(Transform* pParent, const uint16_t drawPriority)
{
	Initialize(pParent, drawPriority);
}

void SlashAttackDrawer::StaticInitialize()
{
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")}});
}
