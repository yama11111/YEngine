#include "SlashAttackDrawer.h"

using YGame::SlashAttackDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

Model* SlashAttackDrawer::spModel_ = nullptr;

SlashAttackDrawer* SlashAttackDrawer::Create(Transform* pParent, const uint16_t drawPriority)
{
	SlashAttackDrawer* newDrawer = new SlashAttackDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void SlashAttackDrawer::StaticInitialize()
{
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void SlashAttackDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	// モデル設定
	obj_->SetModel(spModel_);
}

void SlashAttackDrawer::InsertAnimationTimers()
{
}

void SlashAttackDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
}

void SlashAttackDrawer::UpdateAnimtion()
{
}