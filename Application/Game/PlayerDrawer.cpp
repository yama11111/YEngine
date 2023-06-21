#include "PlayerDrawer.h"

using YGame::PlayerDrawer;
using YGame::Model;

void PlayerDrawer::Initialize(Transform* pParent)
{
	// �I�u�W�F�N�g������
	IDrawer::Initialize(pParent);
	
	// ���f���ݒ�
	pModel_ = Model::CreateCube("player.png");
}

void PlayerDrawer::Update()
{
	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void PlayerDrawer::Draw(const DrawLocation location)
{
	// �`��
	pModel_->SetDrawCommand(obj_.get(), location);
}

void PlayerDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}
