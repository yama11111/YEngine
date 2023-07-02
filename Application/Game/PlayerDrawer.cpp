#include "PlayerDrawer.h"

using YGame::PlayerDrawer;
using YGame::Model;

Model* PlayerDrawer::spModel_ = nullptr;

void PlayerDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, location);

	// ���f���}��
	pModel_ = spModel_;

	shader_ = Model::ShaderType::eToon;
}

void PlayerDrawer::Update()
{
	BaseDrawer::Update();
}

void PlayerDrawer::Draw()
{
	BaseDrawer::Draw();
}

void PlayerDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

PlayerDrawer::PlayerDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

PlayerDrawer::PlayerDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}

void PlayerDrawer::StaticInitialize()
{
	// ���f���ݒ�
	spModel_ = Model::CreateCube("player.png");
}
