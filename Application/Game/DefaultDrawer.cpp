#include "DefaultDrawer.h"

using YGame::DefaultDrawer;
using YGame::Model;

void DefaultDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, location);

	// ���f���ݒ�
	pModel_ = Model::CreateCube("white1x1.png");
}

void DefaultDrawer::Update()
{
	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void DefaultDrawer::Draw()
{
	// �`��
	pModel_->SetDrawCommand(obj_.get(), location_, Model::ShaderType::ePhong);
}

void DefaultDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

DefaultDrawer::DefaultDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

DefaultDrawer::DefaultDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}
