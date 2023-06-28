#include "GameObject.h"
#include <cassert>

using YGame::GameObject;

void GameObject::Initialize(const std::string name, const Transform::Status& status, GameObject* pParent)
{
	// �g�����X�t�H�[������ + ������
	transform_.reset(new Transform(status));
	
	// �e������Ȃ�
	if (pParent)
	{
		// ��� + �e�q�֌W
		pParent_ = pParent;
		transform_->parent_ = &pParent_->transform_->m_;
	}

	// �s��X�V
	transform_->UpdateMatrix();
}

void GameObject::Update()
{
	// ���R���C�_�[�X�V
	if (collider_) { collider_->Update(); }

	// �j�X�V
	transform_->UpdateMatrix();

	// �`��N���X�X�V
	if (drawer_) { drawer_->Update(); }
}

void GameObject::Draw()
{
	// �`��
	if (drawer_) { drawer_->Draw(); }
}

void GameObject::OnCollision()
{
}

void GameObject::SetCollider(BaseCollider* collider)
{
	// �R���C�_�[�N���X�ݒ�
	collider_.reset(collider);

	// null ����Ȃ��Ȃ�
	if (collider_)
	{
		// �R���C�_�[�N���X�e�|�C���^�ݒ�
		collider_->SetParent(transform_.get());
	}
}

void GameObject::SetDrawer(BaseDrawer* drawer)
{
	// �`��N���X�ݒ�
	drawer_.reset(drawer);
	
	// null ����Ȃ��Ȃ�
	if (drawer_)
	{
		// �`��N���X�e�|�C���^�ݒ�
		drawer_->SetParent(transform_.get());
	}
}