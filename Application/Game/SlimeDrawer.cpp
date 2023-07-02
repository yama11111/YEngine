#include "SlimeDrawer.h"

using YGame::SlimeDrawer;
using YGame::Model;

Model* SlimeDrawer::spModel_ = nullptr;

void SlimeDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, location);

	// ���f���ݒ�
	pModel_ = spModel_;

	shader_ = Model::ShaderType::eToon;
}

void SlimeDrawer::Update()
{
	BaseDrawer::Update();
}

void SlimeDrawer::Draw()
{
	BaseDrawer::Draw();
}

void SlimeDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

SlimeDrawer::SlimeDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

SlimeDrawer::SlimeDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}

void SlimeDrawer::StaticInitialize()
{
	spModel_ = Model::LoadObj("slime", true);
}
