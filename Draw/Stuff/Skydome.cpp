#include "Skydome.h"
#include <cassert>

using YGame::Skydome;

void Skydome::Initialize(const Transform::Status status, YGame::Model* pModel)
{
	// null�`�F�b�N
	assert(pModel);
	// ���
	pModel_ = pModel;

	// ����
	obj_.reset(ModelObject::Create(status));
}

void Skydome::Update()
{
	// �X�V
	obj_->UpdateMatrix();
}

void Skydome::Draw()
{
	// �`��
	pModel_->Draw(obj_.get());
}