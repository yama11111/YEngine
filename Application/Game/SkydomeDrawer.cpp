#include "SkydomeDrawer.h"

using YGame::SkydomeDrawer;
using YGame::Model;

void SkydomeDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, location);

	// ���f���ݒ�
	pModel_ = Model::LoadObj("skydome", true);
}

void SkydomeDrawer::Update()
{
	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void SkydomeDrawer::Draw()
{
	// �`��
	pModel_->SetDrawCommand(obj_.get(), location_);
}

void SkydomeDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

SkydomeDrawer::SkydomeDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

SkydomeDrawer::SkydomeDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}
