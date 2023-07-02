#include "DefaultDrawer.h"

using YGame::DefaultDrawer;
using YGame::Model;

Model* DefaultDrawer::spModel_ = nullptr;

void DefaultDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, location);

	// ���f���}��
	pModel_ = spModel_;

	shader_ = Model::ShaderType::eToon;
}

void DefaultDrawer::Update()
{
	BaseDrawer::Update();
}

void DefaultDrawer::Draw()
{
	BaseDrawer::Draw();
}

void DefaultDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

DefaultDrawer::DefaultDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

DefaultDrawer::DefaultDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}


void DefaultDrawer::StaticInitialize()
{
	// ���f���ݒ�
	spModel_ = Model::CreateCube("white1x1.png");
}