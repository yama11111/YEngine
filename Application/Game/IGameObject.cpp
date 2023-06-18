#include "IGameObject.h"
#include <cassert>

using YGame::IGameObject;

void IGameObject::Initialize(
	const Type type, 
	const Transform::Status& status, 
	const float radius, 
	const bool isSlip,
	IDrawer* drawer)
{
	// �j����
	transform_.reset(new Transform());

	// ������
	transform_->Initialize(status);

	// �`��N���X
	SetDrawer(drawer);

	// �R���C�_�[������
	GameObjectCollider::Initialize(type, &transform_->pos_, radius, isSlip);
}

void IGameObject::Update()
{
	// �j�X�V
	transform_->UpdateMatrix();

	// �`��N���X�X�V
	drawer_->Update();
	
	// �R���C�_�[�X�V
	GameObjectCollider::Update();
}

void IGameObject::DrawDebugText(const bool isWindow)
{
	// �E�B���h�E�Ȃ�
	if (isWindow)
	{

	}
}

void IGameObject::SetDrawer(IDrawer* drawer)
{
	// null �Ȃ�
	if (drawer == nullptr && drawer_ == nullptr)
	{
		// �X�^���_�[�h�`��N���X�ݒ�
		// drawer_.reset(�X�^���_�[�h);
	}
	else
	{
		// �`��N���X�ݒ�
		drawer_.reset(drawer);
	}

	// �`��N���X������
	drawer_->Initialize(transform_.get());
}
