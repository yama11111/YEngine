#include "SlashAttackDrawer.h"

using YGame::SlashAttackDrawer;
using YGame::Model;

Model* SlashAttackDrawer::spModel_ = nullptr;

void SlashAttackDrawer::Initialize(Transform* pParent, const uint32_t drawPriority)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, drawPriority);

	// ���f���ݒ�
	obj_->SetGraphic(spModel_);
}

void SlashAttackDrawer::Update()
{
	BaseDrawer::Update();
}

void SlashAttackDrawer::Draw()
{
	BaseDrawer::Draw();
}

void SlashAttackDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{
}

SlashAttackDrawer::SlashAttackDrawer(const uint32_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

SlashAttackDrawer::SlashAttackDrawer(Transform* pParent, const uint32_t drawPriority)
{
	Initialize(pParent, drawPriority);
}

void SlashAttackDrawer::StaticInitialize()
{
	spModel_ = Model::CreateCube("white1x1.png");
}
