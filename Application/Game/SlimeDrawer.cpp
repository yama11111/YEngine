#include "SlimeDrawer.h"

using YGame::SlimeDrawer;
using YGame::Model;

Model* SlimeDrawer::spModel_ = nullptr;

void SlimeDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, location);

	// ���f���ݒ�
	pModel_ = spModel_;
}

void SlimeDrawer::Update()
{
	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void SlimeDrawer::Draw()
{
	// �`��
	pModel_->SetDrawCommand(obj_.get(), location_, Model::ShaderType::ePhong);
}

void SlimeDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

SlimeDrawer::SlimeDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

SlimeDrawer::SlimeDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}

void SlimeDrawer::StaticInitialize()
{
	spModel_ = Model::CreateCube("enemy.png");
}
