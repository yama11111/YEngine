#include "Camera.h"
#include "CalcTransform.h"
#include <cassert>

using YGame::Transform;
using YGame::ViewProjection;
using YGame::Camera;
using YMath::Vector3;
using YMath::MultVec3Mat4;

void Camera::Initialize(const Transform::Status& status, YMath::Vector3* pFollowPos, bool isFollow)
{
	// ������ + ���
	shake_.Initialize();
	pos_ = status.pos_;
	rota_ = status.rota_;
	transform_.Initialize(status);
	vp_.Initialize({});

	pFollowPoint_ = pFollowPos;
	SetIsFollow(isFollow);

	// �X�V
	Update();
}

void Camera::UpdateTarget()
{
	// �Ǐ]���� && �Ǐ]�_���O��ƈႤ�ꏊ�ɂ���Ȃ�
	if (isFollow_ && (vp_.eye_ != *pFollowPoint_))
	{
		// �����_�ɒǏ]�_���
		vp_.target_ = *pFollowPoint_;
	}
	// �����Ȃ�
	else
	{
		// �����̌����Ă�������𒍎��_�Ƃ���
		Vector3 forward = MultVec3Mat4(Vector3(0, 0, 1), transform_.m_);
		vp_.target_ = vp_.eye_ + forward;
	}
}
void Camera::Update()
{
	// �ʒu + ��]�X�V
	transform_.pos_ = pos_;
	transform_.rota_ = rota_;
	
	// �A�t�B���ϊ�
	transform_.UpdateMatrix();
	
	// �J�����V�F�C�N�X�V
	shake_.Update();


	// ���_�X�V
	vp_.eye_ = transform_.pos_;
	// �����_�X�V
	UpdateTarget();
	// ������x�N�g���X�V
	vp_.up_ = MultVec3Mat4(Vector3(0, 1, 0), transform_.m_);

	// �r���[�v���W�F�N�V�����s��X�V
	vp_.UpdateMatrix();
}

void Camera::Shaking(const int swing, const int dekey)
{
	// �J�����V�F�C�N
	shake_.Activate(swing, dekey);
}

YGame::ViewProjection Camera::GetViewProjection()
{
	// �߂�l�p
	YGame::ViewProjection result = vp_;
	
	// �J�����V�F�C�N���Z
	result.eye_ += shake_.Value() / 10.0f;
	result.target_ += shake_.Value() / 10.0f;
	
	// �s��X�V
	result.UpdateMatrix();

	return result;
}

Vector3 Camera::Direction()
{
	// �������v�Z
	Vector3 vel = MultVec3Mat4(Vector3(0, 0, 1), transform_.m_);
	
	return vel.Normalized();
}

void Camera::SetFollowPoint(YMath::Vector3* pFollowPoint, const bool isFollow)
{
	// null�`�F�b�N
	assert(pFollowPoint);
	
	// ���
	pFollowPoint_ = pFollowPoint;
	isFollow_ = isFollow;
}

void Camera::SetIsFollow(const bool isFollow)
{
	// �Ǐ]�_������Ȃ�
	if (pFollowPoint_) 
	{
		// ���
		isFollow_ = isFollow; 
	}
	// �����Ȃ�
	else 
	{
		// �Ǐ]�_���Ȃ�
		isFollow_ = false; 
	}
}
