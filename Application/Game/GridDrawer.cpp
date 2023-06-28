#include "GridDrawer.h"

using YGame::GridDrawer;
using YGame::Model;

void GridDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, location);

	// ���f���ݒ�
	pModel_ = Model::LoadObj("grid", true);
}

void GridDrawer::Update()
{
	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void GridDrawer::Draw()
{
	// �`��
	pModel_->SetDrawCommand(obj_.get(), location_, Model::ShaderType::ePhong);
}

void GridDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

GridDrawer::GridDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

GridDrawer::GridDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}
