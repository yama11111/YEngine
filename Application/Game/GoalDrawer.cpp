#include "GoalDrawer.h"

using YGame::GoalDrawer;
using YGame::Model;

Model* GoalDrawer::spModel_ = nullptr;

void GoalDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);
	obj_->transform_.scale_ = YMath::Vector3(1.0f, 1.0f, 15.0f);

	cbColor_->data_.baseColor = YMath::Vector4(1.0f, 1.0f, 0.0f, 0.25f);

	// モデル挿入
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelToon";
}

void GoalDrawer::Update()
{
	BaseDrawer::Update();

	VisibleUpdate();
}

void GoalDrawer::Draw()
{
	BaseDrawer::Draw();
}

void GoalDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{

}

GoalDrawer::GoalDrawer(const uint16_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

GoalDrawer::GoalDrawer(Transform* pParent, const uint16_t drawPriority)
{
	Initialize(pParent, drawPriority);
}


void GoalDrawer::StaticInitialize()
{
	// モデル設定
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}