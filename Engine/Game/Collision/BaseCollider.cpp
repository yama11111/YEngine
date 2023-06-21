#include "BaseCollider.h"
#include <cassert>

using YGame::BaseCollider;
using YMath::Vector3;

void BaseCollider::Initialize(
	const uint32_t attribute, 
	const uint32_t mask, 
	Vector3* pPos, 
	const float radius, 
	const bool isSlip)
{
	// �����ݒ�
	SetAttribute(attribute);
	
	// �}�X�N�ݒ�
	SetMask(mask);

	// �ʒu�|�C���^�ύX
	SetPosPointer(pPos);
	
	// ���̔��a
	SetSphereRadius(radius);

	// ���蔲���t���O�ݒ�
	SetIsSlip(isSlip);
}

void BaseCollider::Update()
{
	// ���̒��S�_
	SetSphereCenter(*pPos_);
}

void BaseCollider::SetPosPointer(Vector3* pPos)
{
	// null�`�F�b�N
	assert(pPos);

	// ���
	pPos_ = pPos;
}
