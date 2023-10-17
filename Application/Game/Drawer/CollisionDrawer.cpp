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

CollisionDrawer* CollisionDrawer::Create(Transform* pParent, const float radius, const size_t drawPriority)
{
	CollisionDrawer* newDrawer = new CollisionDrawer();

	newDrawer->Initialize(pParent, drawPriority);
	newDrawer->SetRadius(radius);

	return newDrawer;
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

void CollisionDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

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
