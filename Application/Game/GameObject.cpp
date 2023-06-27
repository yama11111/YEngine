#include "GameObject.h"
#include <cassert>

using YGame::GameObject;

void GameObject::Initialize(const Transform::Status& status)
{
	// �g�����X�t�H�[������ + ������
	transform_.reset(new Transform(status));
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
	drawer_->Draw();
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