#include "ScrollCamera.h"

using YGame::ScrollCamera;
using YGame::ViewProjection;
using YGame::Camera;
using YMath::Vector3;

void ScrollCamera::Initialize(const Vector3 distance, Vector3* pFollowPoint, const Vector3 tolerance)
{
	// �Ǐ]�ʒu
	Vector3 followPoint;

	// �Ǐ]�_������Ȃ�
	if (pFollowPoint)
	{
		// ���
		followPoint = *pFollowPoint;
	}

	// ������ + ���
	Camera::Initialize(followPoint + distance, pFollowPoint, true);

	distance_ = distance;
	tolerance_ = tolerance;
}

void ScrollCamera::Update()
{
	// �Ǐ]�ʒu
	Vector3 followPoint;

	// �Ǐ]�_������Ȃ�
	if (pFollowPoint_)
	{
		// ���
		followPoint = *pFollowPoint_;
	}

	// ���_�� �Ǐ]�_ + ���� �̈ʒu��
	pos_ = followPoint + distance_;

	// �J�����X�V
	Camera::Update();
}

void ScrollCamera::SetFollowPoint(Vector3* pFollowPoint)
{
	// �Ǐ]�_
	Camera::SetFollowPoint(pFollowPoint);
}
