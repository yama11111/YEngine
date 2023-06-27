#include "BlockDrawer.h"

using YGame::BlockDrawer;
using YGame::Model;

void BlockDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, location);

	// ���f���ݒ�
	pModel_ = Model::CreateCube("block.png");
}

void BlockDrawer::Update()
{
	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void BlockDrawer::Draw()
{
	// �`��
	pModel_->SetDrawCommand(obj_.get(), location_);
}

void BlockDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

BlockDrawer::BlockDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

BlockDrawer::BlockDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}
