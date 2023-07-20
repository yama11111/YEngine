#include "BlockDrawer.h"

using YGame::BlockDrawer;
using YGame::Model;
using YMath::Vector3;

Model* BlockDrawer::spModel_ = nullptr;

void BlockDrawer::Initialize(Transform* pParent, const uint32_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);
	transform_->scale_ = Vector3(1.0f, 1.0f, 15.0f);

	cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);

	// モデル設定
	obj_->SetGraphic(spModel_);

	shaderKey_ = "ModelPhong";
}

void BlockDrawer::Update()
{
	BaseDrawer::Update();

	VisibleUpdate();
}

void BlockDrawer::Draw()
{
	BaseDrawer::Draw();
}

void BlockDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{

}

BlockDrawer::BlockDrawer(const uint32_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

BlockDrawer::BlockDrawer(Transform* pParent, const uint32_t drawPriority)
{
	Initialize(pParent, drawPriority);
}

void BlockDrawer::StaticInitialize()
{
	spModel_ = Model::LoadObj("soil", true);
}
