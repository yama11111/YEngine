#include "CloudDrawer.h"

using YGame::CloudDrawer;
using YGame::Model;

Model* CloudDrawer::spModel_ = nullptr;

void CloudDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, location);

	color_->SetAlpha(0.4f);

	// ���f���}��
	pModel_ = spModel_;

	shader_ = Model::ShaderType::eToon;
}

void CloudDrawer::Update()
{
	BaseDrawer::Update();
}

void CloudDrawer::Draw()
{
	BaseDrawer::Draw();
}

void CloudDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

CloudDrawer::CloudDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

CloudDrawer::CloudDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}


void CloudDrawer::StaticInitialize()
{
	// ���f���ݒ�
	spModel_ = Model::CreateCube("white1x1.png");
}