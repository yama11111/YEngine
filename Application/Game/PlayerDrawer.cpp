#include "PlayerDrawer.h"

using YGame::PlayerDrawer;
using YGame::Model;

void PlayerDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, location);

	// ���f���ݒ�
	pModel_ = Model::LoadObj("player", true);
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

}
