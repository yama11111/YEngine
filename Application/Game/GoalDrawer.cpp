#include "GoalDrawer.h"

using YGame::GoalDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

Model* GoalDrawer::spModel_ = nullptr;

GoalDrawer* GoalDrawer::Create(Transform* pParent, const uint16_t drawPriority)
{
	GoalDrawer* newDrawer = new GoalDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void GoalDrawer::StaticInitialize()
{
	// ���f���ݒ�
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void GoalDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, drawPriority);
	obj_->transform_.scale_ = Vector3(1.0f, 1.0f, 15.0f);

	cbColor_->data_.baseColor = Vector4(1.0f, 1.0f, 0.0f, 0.25f);

	// ���f���}��
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelToon";
}

void GoalDrawer::InsertAnimationTimers()
{
}

void GoalDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
}

void GoalDrawer::UpdateAnimation()
{
}