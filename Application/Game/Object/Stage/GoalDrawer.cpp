#include "GoalDrawer.h"
#include "DrawObjectForModel.h"
#include "ViewProjectionManager.h"

#include "CircleShadowManager.h"

using YGame::GoalDrawer;
using YGame::ViewProjectionManager;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	Model* pModel = nullptr;
	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();
}

std::unique_ptr<GoalDrawer> GoalDrawer::Create(const DrawerInitSet& init)
{
	std::unique_ptr<GoalDrawer> newDrawer = std::make_unique<GoalDrawer>();

	newDrawer->Initialize(init);

	return std::move(newDrawer);
}

void GoalDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void GoalDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);

	InsertConstBuffer("Goal", CircleShadowManager::GetInstance()->CBPtr(CircleShadowManager::Key::eWorld_2));
	
	SetShaderTag("ModelToon");
	
	transform_.scale_ = Vector3(1.0f, 1.0f, 1.0f);
	
	cbColor_->data_.baseColor = Vector4(1.0f, 1.0f, 0.0f, 0.25f);
}

void GoalDrawer::InitializeObjects()
{
	InsertObject("Goal", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
}