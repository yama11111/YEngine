#include "SphereCollider.h"

using YGame::SphereCollider;
using YMath::Vector3;

void SphereCollider::Initialize(
	const Vector3& offset,
	const uint32_t attribute, const uint32_t mask,
	const float radius,
	const bool isSlip)
{
	// �e�|�C���^ null �ŏ�����
	Initialize(nullptr, offset, attribute, mask, radius, isSlip);
}

void SphereCollider::Initialize(
	Transform* pParent, const Vector3& offset, 
	const uint32_t attribute, const uint32_t mask, 
	const float radius, 
	const bool isSlip)
{
	// ���N���X������
	BaseCollider::Initialize(pParent, offset, attribute, mask, isSlip);

	// �`�� : ��
	shapeType_ = ShapeType::eSphere;

	// ���a
	Sphere::SetSphereRadius(radius);

	// �X�V
	Update();
}

void SphereCollider::Update()
{
	// ���S�_
	Vector3 center = offset_;

	// �e������Ȃ�
	if (pParent_)
	{
		// �ʒu�����炷
		center += pParent_->pos_;
	}

	// ���S�_�X�V
	SetSphereCenter(center);
}

SphereCollider::SphereCollider(
	const Vector3& offset,
	const uint32_t attribute, const uint32_t mask,
	const float radius,
	const bool isSlip) :
	BaseCollider(offset, attribute, mask, isSlip)
{
	Sphere::SetSphereRadius(radius);
}

SphereCollider::SphereCollider(
	Transform* pParent, const Vector3& offset, 
	const uint32_t attribute, const uint32_t mask, 
	const float radius, 
	const bool isSlip) : 
	BaseCollider(pParent, offset, attribute, mask, isSlip)
{
	Sphere::SetSphereRadius(radius);
}
