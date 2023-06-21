#include "BlockDrawer.h"

using YGame::BlockDrawer;
using YGame::Model;

void BlockDrawer::Initialize(Transform* pParent)
{
	// �I�u�W�F�N�g������
	IDrawer::Initialize(pParent);

	// ���f���ݒ�
	pModel_ = Model::CreateCube("block.png");
}

void BlockDrawer::Update()
{
	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void BlockDrawer::Draw(const DrawLocation location)
{
	// �`��
	pModel_->SetDrawCommand(obj_.get(), location);
}

void BlockDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}
