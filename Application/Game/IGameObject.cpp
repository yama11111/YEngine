#include "IGameObject.h"
#include <cassert>

using YGame::IGameObject;

void IGameObject::Initialize(const Transform::Status& status)
{
	// �j����
	core_.reset(new Transform());

	// ������
	core_->Initialize(status);


	// �I�u�W�F�N�g����
	obj_.reset(Model::Object::Create());

	// �e�q�֌W�ݒ�
	obj_->parent_ = &core_->m_;
}

void IGameObject::SetModel(Model* pModel)
{
	// null�`�F�b�N
	assert(pModel);

	// ���
	pModel_ = pModel;
}
