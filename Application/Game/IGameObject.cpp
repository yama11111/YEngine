#include "IGameObject.h"
#include <cassert>

using YGame::IGameObject;

void IGameObject::Initialize(
	const Transform::Status& status,
	IDrawer* drawer,
	const DrawLocation location)
{
	// �j����
	transform_.reset(new Transform());

	// ������
	transform_->Initialize(status);

	// �`��N���X
	SetDrawer(drawer);

	// �`��ʒu�ݒ�
	SetDrawLocation(location);
}

void IGameObject::Update()
{
	// �j�X�V
	transform_->UpdateMatrix();

	// �`��N���X�X�V
	drawer_->Update();
}

void IGameObject::Draw()
{
	// �`��
	drawer_->Draw(location_);
}

void IGameObject::SetDrawer(IDrawer* drawer)
{
	// null �Ȃ�
	if (drawer == nullptr)
	{
		// �X�^���_�[�h�`��N���X�ݒ�
		//drawer_.reset(�X�^���_�[�h);
	}
	else
	{
		// �`��N���X�ݒ�
		drawer_.reset(drawer);
	}

	// �`��N���X������
	drawer_->Initialize(transform_.get());
}

void IGameObject::SetDrawLocation(const DrawLocation location)
{
	// ���
	location_ = location;
}
