#include "BlockDrawer.h"

using YGame::BlockDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

Model* BlockDrawer::spModel_ = nullptr;

BlockDrawer* BlockDrawer::Create(Transform* pParent, const uint16_t drawPriority)
{
	BlockDrawer* newDrawer = new BlockDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void BlockDrawer::StaticInitialize()
{
	spModel_ = Model::LoadObj("soil", true);
}

void BlockDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);
	obj_->transform_.scale_ = Vector3(1.0f, 1.0f, 15.0f);

	cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);

	// モデル設定
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelPhong";
}

void BlockDrawer::InsertAnimationTimers()
{
}

void BlockDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
}

void BlockDrawer::UpdateAnimation()
{
}