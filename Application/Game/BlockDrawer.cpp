#include "BlockDrawer.h"

using YGame::BlockDrawer;
using YGame::Model;
using YMath::Vector3;

Model* BlockDrawer::spModel_ = nullptr;

void BlockDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, location);
	obj_->scale_ = Vector3(1.0f, 1.0f, 15.0f);

	material_->SetAmbient(Vector3(0.8f, 0.8f, 0.8f));

	// ���f���ݒ�
	pModel_ = spModel_;

	shader_ = Model::ShaderType::eDefault;
}

void BlockDrawer::Update()
{
	obj_->UpdateMatrix();
}

void BlockDrawer::Draw()
{
	BaseDrawer::Draw();
}

void BlockDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
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

void BlockDrawer::StaticInitialize()
{
	spModel_ = Model::LoadObj("soil", true);
}
