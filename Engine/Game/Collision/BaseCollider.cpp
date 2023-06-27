#include "BaseCollider.h"
#include <cassert>

using YGame::BaseCollider;
using YMath::Vector3;

void BaseCollider::Initialize(
	const Vector3& offset, 
	const uint32_t attribute, const uint32_t mask, 
	const bool isSlip)
{
	// �e�|�C���^ null �ŏ�����
	Initialize(nullptr, offset, attribute, mask, isSlip);
}

void BaseCollider::Initialize(
	Transform* pParent, const Vector3& offset, 
	const uint32_t attribute, const uint32_t mask, 
	const bool isSlip)
{
	// �e�g�����X�t�H�[���|�C���^�ݒ�
	SetParent(pParent);

	// �I�t�Z�b�g�ݒ�
	SetOffset(offset);

	// �����ݒ�
	SetAttribute(attribute);

	// �}�X�N�ݒ�
	SetMask(mask);

	// ���蔲���t���O�ݒ�
	SetIsSlip(isSlip);
}

void BaseCollider::SetParent(Transform* pParent)
{
	// �e�g�����X�t�H�[���|�C���^�ݒ�
	pParent_ = pParent;
}

BaseCollider::BaseCollider(
	const Vector3& offset, 
	const uint32_t attribute, const uint32_t mask, 
	const bool isSlip) : 
	pParent_(nullptr), offset_(offset),
	attribute_(attribute), mask_(mask),
	isSlip_(isSlip)
{}

BaseCollider::BaseCollider(
	Transform* pParent, const Vector3& offset, 
	const uint32_t attribute, const uint32_t mask, 
	const bool isSlip) :
	pParent_(pParent), offset_(offset),
	attribute_(attribute), mask_(mask),
	isSlip_(isSlip)
{}
