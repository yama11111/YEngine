#include "IGameObject.h"
#include <cassert>

using YGame::IGameObject;

void IGameObject::Initialize(
	const Type type, 
	const Transform::Status& status, 
	const float radius, 
	const bool isSlip)
{
	// �j����
	transform_.reset(new Transform());

	// ������
	transform_->Initialize(status);


	// �I�u�W�F�N�g����
	obj_.reset(Model::Object::Create());

	// �e�q�֌W�ݒ�
	obj_->parent_ = &transform_->m_;


	// �R���C�_�[������
	GameObjectCollider::Initialize(type, &transform_->pos_, radius, isSlip);
}

void IGameObject::Update()
{
	// �j�X�V
	transform_->UpdateMatrix();

	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
	
	// �R���C�_�[�X�V
	GameObjectCollider::Update();
}

void IGameObject::SetModel(Model* pModel)
{
	// null�`�F�b�N
	assert(pModel);

	// ���
	pModel_ = pModel;
}
