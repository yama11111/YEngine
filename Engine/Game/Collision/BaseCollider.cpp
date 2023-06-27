#include "BaseCollider.h"
#include <cassert>

using YGame::BaseCollider;
using YMath::Vector3;

void BaseCollider::Initialize(
	const Vector3& offset, 
	const uint32_t attribute, const uint32_t mask, 
	const bool isSlip)
{
	// 親ポインタ null で初期化
	Initialize(nullptr, offset, attribute, mask, isSlip);
}

void BaseCollider::Initialize(
	Transform* pParent, const Vector3& offset, 
	const uint32_t attribute, const uint32_t mask, 
	const bool isSlip)
{
	// 親トランスフォームポインタ設定
	SetParent(pParent);

	// オフセット設定
	SetOffset(offset);

	// 属性設定
	SetAttribute(attribute);

	// マスク設定
	SetMask(mask);

	// すり抜けフラグ設定
	SetIsSlip(isSlip);
}

void BaseCollider::SetParent(Transform* pParent)
{
	// 親トランスフォームポインタ設定
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
