#include "GoalDrawer.h"

using YGame::GoalDrawer;
using YGame::Model;

Model* GoalDrawer::spModel_ = nullptr;

void GoalDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, location);
	obj_->scale_ = YMath::Vector3(1.0f, 1.0f, 15.0f);

	color_->SetRGBA(YMath::Vector4(1.0f, 1.0f, 0.0f, 0.25f));

	// モデル挿入
	pModel_ = spModel_;

	shader_ = Model::ShaderType::eToon;
}

void GoalDrawer::Update()
{
	obj_->UpdateMatrix();
}

void GoalDrawer::Draw()
{
	BaseDrawer::Draw();
}

void GoalDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{

}

GoalDrawer::GoalDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

GoalDrawer::GoalDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}


void GoalDrawer::StaticInitialize()
{
	// モデル設定
	spModel_ = Model::CreateCube("white1x1.png");
}