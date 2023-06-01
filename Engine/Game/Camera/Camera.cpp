#include "Camera.h"
#include "CalcTransform.h"
#include <cassert>

using YGame::Transform;
using YGame::ViewProjection;
using YGame::Camera;
using YMath::Vector3;
using YMath::MultVec3Mat4;

void Camera::Initialize(const Vector3 pos, const Vector3 rota)
{
	// ������ + ���
	shake_.Initialize();
	pos_ = pos;
	rota_ = rota;
	transform_.Initialize({ pos_, rota_, {1.0f,1.0f,1.0f} });
	vp_.Initialize();

	pFollowPoint_ = nullptr;
	SetIsFollow(false);

	// �X�V
	Update();
}

void Camera::Initialize(const Vector3 pos, Vector3* pFollowPoint, bool isFollow)
{
	// null�`�F�b�N
	assert(pFollowPoint);
	// ���
	pFollowPoint_ = pFollowPoint;

	// ������ + ���
	shake_.Initialize();
	pos_ = pos;
	rota_ = {};
	transform_.Initialize({ pos_, rota_, {1.0f,1.0f,1.0f} });
	vp_.Initialize();
	
	SetIsFollow(isFollow);

	isSmooth_ = false;
	moveTimer_.Initialize(0);
	moveEase_.Initialize({}, {}, 0.0f);

	// �X�V
	Update();
}

void Camera::UpdateTarget()
{
	// �Ǐ]�_������ && �Ǐ]����Ȃ�
	if (pFollowPoint_ && isFollow_)
	{
		// �����_�ɒǏ]�_���
		vp_.target_ = *pFollowPoint_;
	}
	// ����ȊO�Ȃ�
	else
	{
		// �����̌����Ă�������𒍎��_�Ƃ���
		Vector3 forward = MultVec3Mat4(Vector3(0, 0, 1), transform_.m_);
		vp_.target_ = vp_.eye_ + forward;
	}
}
void Camera::Update()
{
	if (isSmooth_)
	{
		moveTimer_.Update();
		pos_ = moveEase_.Out(moveTimer_.Ratio());

		if (moveTimer_.IsEnd())
		{
			isSmooth_ = false;
		}
	}

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

void Camera::SmoothMoving(const unsigned int frame, const Vector3& pos, const float exponent)
{
	moveTimer_.Initialize(frame);
	moveTimer_.SetActive(true);

	moveEase_.Initialize(pos_, pos, exponent);

	isSmooth_ = true;
}

void Camera::Shaking(const float swing, const float dekey, const float place)
{
	// �J�����V�F�C�N
	shake_.Activate(swing, dekey, place);
}

ViewProjection Camera::GetViewProjection()
{
	// �߂�l�p
	ViewProjection result = vp_;
	
	// �J�����V�F�C�N���Z
	result.eye_ += shake_.Value();
	result.target_ += shake_.Value();
	
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

void Camera::SetFollowPoint(Vector3* pFollowPoint)
{
	// ���
	pFollowPoint_ = pFollowPoint;
	
	// null�Ȃ�
	if (pFollowPoint == nullptr)
	{
		// �Ǐ]���Ȃ�
		isFollow_ = false;
	}
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
		// �Ǐ]���Ȃ�
		isFollow_ = false; 
	}
}
