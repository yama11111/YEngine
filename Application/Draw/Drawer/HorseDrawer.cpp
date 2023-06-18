#include "HorseDrawer.h"

using YGame::HorseDrawer;
using YGame::Model;

void HorseDrawer::Initialize(Transform* pParent)
{
	// �I�u�W�F�N�g������
	IDrawer::Initialize(pParent);

	// ���f���ݒ�
	pModel_ = Model::CreateCube("horse.png");
}

void HorseDrawer::Update()
{
	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void HorseDrawer::Draw(const DrawLocation location)
{
	// �`��
	pModel_->SetDrawCommand(obj_.get(), location);
}

void HorseDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}
