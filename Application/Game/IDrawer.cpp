#include "IDrawer.h"
#include <cassert>

using YGame::IDrawer;

YGame::ViewProjection* IDrawer::spVP_ = nullptr;

void IDrawer::Initialize(Transform* pParent)
{
	// �I�u�W�F�N�g����
	obj_.reset(Model::Object::Create());

	// �e�q�֌W�ݒ�
	obj_->parent_ = &pParent->m_;

	// �r���[�v���W�F�N�V�����ݒ�
	obj_->SetViewProjection(spVP_);
}

void IDrawer::StaticInitialize(ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);

	// ���
	spVP_ = pVP;
}
