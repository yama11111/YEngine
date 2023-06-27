#include "BaseDrawer.h"
#include <cassert>

using YGame::BaseDrawer;

YGame::ViewProjection* BaseDrawer::spVP_ = nullptr;

void BaseDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g����
	obj_.reset(Model::Object::Create());

	// �e�ݒ�
	SetParent(pParent);

	// �r���[�v���W�F�N�V�����ݒ�
	obj_->SetViewProjection(spVP_);

	// �`��ʒu
	location_ = location;
}

void BaseDrawer::SetParent(Transform* pParent)
{
	// �e�g�����X�t�H�[���|�C���^�ݒ�
	pParent_ = pParent;

	// null ����Ȃ��Ȃ�
	if (pParent_)
	{
		// �e�q�֌W�ݒ�
		obj_->parent_ = &pParent_->m_;
	}
	// �Ⴄ�Ȃ�
	else
	{
		// �e�q�֌W������
		obj_->parent_ = nullptr;
	}
}

void BaseDrawer::StaticInitialize(ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);

	// ���
	spVP_ = pVP;
}

BaseDrawer::BaseDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

BaseDrawer::BaseDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}
