#include "CollisionDrawer.h"

using YGame::CollisionDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

Model* CollisionDrawer::spModel_ = nullptr;

CollisionDrawer* CollisionDrawer::Create(Transform* pParent, const float radius, const size_t drawPriority)
{
	CollisionDrawer* newDrawer = new CollisionDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void CollisionDrawer::LoadResource()
{
	// ���f���ݒ�
	spModel_ = Model::LoadObj("sphere", true);
}

std::string CollisionDrawer::Name()
{
	return "Collision";
}

void CollisionDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, drawPriority);

	isVisibleUpdate_ = false;

	cbColor_->data_.baseColor = { 1.0f,0.0f,1.0f,0.5f };

	//cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);

	// ���f���}��
	//obj_->SetModel(spModel_);
	obj_->SetModel(nullptr);

	shaderKey_ = "ModelPhong";
}

void CollisionDrawer::SetRadius(const float radius)
{
	obj_->transform_.scale_ = Vector3(radius, radius, radius);
}
