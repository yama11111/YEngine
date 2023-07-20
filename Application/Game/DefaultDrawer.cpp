#include "DefaultDrawer.h"

using YGame::DefaultDrawer;
using YGame::Model;

Model* DefaultDrawer::spModel_ = nullptr;

void DefaultDrawer::Initialize(Transform* pParent, const uint32_t drawPriority)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, drawPriority);

	// ���f���}��
	obj_->SetGraphic(spModel_);

	shaderKey_ = "ModelToon";
}

void DefaultDrawer::Update()
{
	BaseDrawer::Update();
	
	VisibleUpdate();
}

void DefaultDrawer::Draw()
{
	BaseDrawer::Draw();
}

void DefaultDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{

}

DefaultDrawer::DefaultDrawer(const uint32_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

DefaultDrawer::DefaultDrawer(Transform* pParent, const uint32_t drawPriority)
{
	Initialize(pParent, drawPriority);
}


void DefaultDrawer::StaticInitialize()
{
	// ���f���ݒ�
	spModel_ = Model::CreateCube("white1x1.png");
}