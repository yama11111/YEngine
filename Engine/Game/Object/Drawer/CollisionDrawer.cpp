#include "CollisionDrawer.h"
#include "DrawObjectForModel.h"
#include "ViewProjectionManager.h"

using YGame::CollisionDrawer;
using YGame::ViewProjectionManager;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	Model* pModel = nullptr;
	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();
}

std::unique_ptr<CollisionDrawer> CollisionDrawer::Create(const DrawerInitSet& init, const float radius)
{
	std::unique_ptr<CollisionDrawer> newDrawer = std::make_unique<CollisionDrawer>();

	newDrawer->Initialize(init);
	newDrawer->SetRadius(radius);

	return std::move(newDrawer);
}

void CollisionDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::LoadObj("sphere", true);
}

std::string CollisionDrawer::Name()
{
	return "Collision";
}

void CollisionDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);


	isVisibleUpdate_ = false;

	cbColor_->data_.baseColor = { 1.0f,0.0f,1.0f,0.5f };

	SetShaderTag("ModelPhong");
}

void CollisionDrawer::InitializeObjects()
{
	InsertObject("Sphere", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
}

void CollisionDrawer::SetRadius(const float radius)
{
	transform_.scale_ = Vector3(radius, radius, radius);
}
