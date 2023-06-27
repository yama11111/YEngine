#include "HorseDrawer.h"

using YGame::HorseDrawer;
using YGame::Model;

void HorseDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, location);

	// ���f���ݒ�
	pModel_ = Model::CreateCube("face.png");
}

void HorseDrawer::Update()
{
	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void HorseDrawer::Draw()
{
	// �`��
	pModel_->SetDrawCommand(obj_.get(), location_);
}

void HorseDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

HorseDrawer::HorseDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

HorseDrawer::HorseDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}
