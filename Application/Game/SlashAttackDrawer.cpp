#include "SlashAttackDrawer.h"

using YGame::SlashAttackDrawer;
using YGame::Model;

Model* SlashAttackDrawer::spModel_ = nullptr;

void SlashAttackDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, location);

	// ���f���ݒ�
	pModel_ = spModel_;
}

void SlashAttackDrawer::Update()
{
	BaseDrawer::Update();
}

void SlashAttackDrawer::Draw()
{
	BaseDrawer::Draw();
}

void SlashAttackDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{
}

SlashAttackDrawer::SlashAttackDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

SlashAttackDrawer::SlashAttackDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}

void SlashAttackDrawer::StaticInitialize()
{
	spModel_ = Model::CreateCube("white1x1.png");
}
