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
	// 属性設定
	SetAttribute(attribute);
	
	// マスク設定
	SetMask(mask);

	// 位置ポインタ変更
	SetPosPointer(pPos);
	
	// 球の半径
	SetSphereRadius(radius);

	// すり抜けフラグ設定
	SetIsSlip(isSlip);
}

void BaseCollider::Update()
{
	// 球の中心点
	SetSphereCenter(*pPos_);
}

void BaseCollider::SetPosPointer(Vector3* pPos)
{
	// nullチェック
	assert(pPos);

	// 代入
	pPos_ = pPos;
}
