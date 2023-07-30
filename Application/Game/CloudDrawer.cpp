#include "CloudDrawer.h"

using YGame::CloudDrawer;
using YGame::Model;

Model* CloudDrawer::spModel_ = nullptr;

CloudDrawer* CloudDrawer::Create(Transform* pParent, const uint16_t drawPriority)
{
	CloudDrawer* newDrawer = new CloudDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void CloudDrawer::StaticInitialize()
{
	// ���f���ݒ�
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void CloudDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, drawPriority);

	cbColor_->data_.baseColor.a_ = 0.4f;

	// ���f���}��
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelToon";
}

void CloudDrawer::InsertAnimationTimers()
{
}

void CloudDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
}

void CloudDrawer::UpdateAnimtion()
{
}