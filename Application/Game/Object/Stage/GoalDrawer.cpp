#include "GoalDrawer.h"
#include "DrawObjectForModel.h"

using YGame::GoalDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	Model* pModel = nullptr;
}

std::unique_ptr<GoalDrawer> GoalDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	std::unique_ptr<GoalDrawer> newDrawer = std::make_unique<GoalDrawer>();

	newDrawer->Initialize(pParent, drawPriority);

	return std::move(newDrawer);
}

void GoalDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void GoalDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	SetShaderTag("ModelToon");
	
	transform_.scale_ = Vector3(1.0f, 1.0f, 1.0f);
	
	cbColor_->data_.baseColor = Vector4(1.0f, 1.0f, 0.0f, 0.25f);
}

void GoalDrawer::InitializeObjects()
{
	InsertObject("Goal", DrawObjectForModel::Create({}, spVP_, pModel));
}