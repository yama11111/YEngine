#include "EarthDrawer.h"
#include "SkydomeDrawer.h"

using YGame::EarthDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

Model* EarthDrawer::spModel_ = nullptr;

EarthDrawer* EarthDrawer::Create(Transform* pParent, const uint16_t drawPriority)
{
	EarthDrawer* newDrawer = new EarthDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void EarthDrawer::StaticInitialize()
{
	// モデル設定
	spModel_ = Model::LoadObj("earth", true);
}

void EarthDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	//obj_->transform_.scale_ = { 32.0f,32.0f,32.0f };

	isVisibleUpdate_ = false;

	cbColor_->data_.baseColor = Vector4(0.1f, 0.4f, 0.1f, 1.0f);
	cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);

	// モデル挿入
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelPhong";
}

void EarthDrawer::InsertAnimationTimers()
{
}

void EarthDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
}

void EarthDrawer::UpdateAnimation()
{
}