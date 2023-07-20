#include "CloudDrawer.h"

using YGame::CloudDrawer;
using YGame::Model;

Model* CloudDrawer::spModel_ = nullptr;

void CloudDrawer::Initialize(Transform* pParent, const uint32_t drawPriority)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, drawPriority);

	cbColor_->data_.baseColor.a_ = 0.4f;

	// ���f���}��
	obj_->SetGraphic(spModel_);

	shaderKey_ = "ModelToon";
}

void CloudDrawer::Update()
{
	BaseDrawer::Update();

	VisibleUpdate();
}

void CloudDrawer::Draw()
{
	BaseDrawer::Draw();
}

void CloudDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{

}

CloudDrawer::CloudDrawer(const uint32_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

CloudDrawer::CloudDrawer(Transform* pParent, const uint32_t drawPriority)
{
	Initialize(pParent, drawPriority);
}


void CloudDrawer::StaticInitialize()
{
	// ���f���ݒ�
	spModel_ = Model::CreateCube("white1x1.png");
}