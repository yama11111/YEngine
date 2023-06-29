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
}

void PlayerDrawer::Update()
{
	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void PlayerDrawer::Draw()
{
	// �`��
	pModel_->SetDrawCommand(obj_.get(), location_, Model::ShaderType::ePhong);
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
