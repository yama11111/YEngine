#include "ScrollCamera.h"

using YGame::ScrollCamera;
using YGame::ViewProjection;
using YGame::Camera;
using YMath::Vector3;

void ScrollCamera::Initialize(const Vector3 distance, Vector3* pFollowPoint, const Vector3 tolerance)
{
	// ������ + ���
	Camera::Initialize(*pFollowPoint + distance, pFollowPoint);

	distance_ = distance;
	tolerance_ = tolerance;
}

void ScrollCamera::Update()
{
	// ���_�� �Ǐ]�_ + ���� �̈ʒu��
	pos_ = *pFollowPoint_ + distance_;

	// �J�����X�V
	Camera::Update();
}
