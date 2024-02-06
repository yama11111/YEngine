#include "CollisionDrawer.h"
#include "DrawObjectForModel.h"

using YGame::CollisionDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	Model* pModel = nullptr;
}

std::unique_ptr<CollisionDrawer> CollisionDrawer::Create(
	Transform* pParent, YMath::Vector3* pParentWorldPos, const float radius, const size_t drawPriority)
{
	std::unique_ptr<CollisionDrawer> newDrawer = std::make_unique<CollisionDrawer>();

	newDrawer->Initialize(pParent, pParentWorldPos, drawPriority);
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

void CollisionDrawer::Initialize(Transform* pParent, YMath::Vector3* pParentWorldPos, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, pParentWorldPos, drawPriority);


	isVisibleUpdate_ = false;

	cbColor_->data_.baseColor = { 1.0f,0.0f,1.0f,0.5f };

	SetShaderTag("ModelPhong");
}

void CollisionDrawer::InitializeObjects()
{
	InsertObject("Sphere", DrawObjectForModel::Create({}, spVP_, pModel));
}

void CollisionDrawer::SetRadius(const float radius)
{
	transform_.scale_ = Vector3(radius, radius, radius);
}
