#include "SlimeDrawer.h"

using YGame::SlimeDrawer;

void SlimeDrawer::Initialize(Transform* pParent)
{
	// �I�u�W�F�N�g������
	IDrawer::Initialize(pParent);
	
	// ���f���ݒ�
	pModel_ = Model::CreateCube("enemy.png");
}

void SlimeDrawer::Update()
{
	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void SlimeDrawer::Draw(const DrawLocation location)
{
	// �`��
	pModel_->SetDrawCommand(obj_.get(), location);
}

void SlimeDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}
