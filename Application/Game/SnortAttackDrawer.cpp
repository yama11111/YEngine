#include "SnortAttackDrawer.h"

using YGame::SnortAttackDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

Model* SnortAttackDrawer::spModel_ = nullptr;

SnortAttackDrawer* SnortAttackDrawer::Create(Transform* pParent, const uint16_t drawPriority)
{
	SnortAttackDrawer* newDrawer = new SnortAttackDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void SnortAttackDrawer::StaticInitialize()
{
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void SnortAttackDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	// モデル設定
	obj_->SetModel(spModel_);
}

void SnortAttackDrawer::InsertAnimationTimers()
{
}

void SnortAttackDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
}

void SnortAttackDrawer::UpdateAnimtion()
{
}