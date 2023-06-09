#include "GameObjectCollider.h"
#include <cassert>

using YGame::GameObjectCollider;
using YMath::Vector3;


void GameObjectCollider::OnCollision(const GameObjectCollider* pPair)
{
}

bool GameObjectCollider::IsSlip() const
{
	return isSlip_;
}

void GameObjectCollider::Initialize(
	const Type type, 
	Vector3* pPos, const float radius, 
	const bool isSlip)
{
	SetType(type);
	SetPosPointer(pPos);
	SetSphereCenter(*pPos_);
	SetSphereRadius(radius);
	SetIsSlip(isSlip);
}

void GameObjectCollider::Update()
{
	// 位置更新
	SetSphereCenter(*pPos_);
}

void GameObjectCollider::SetType(const Type type)
{
	type_ = type;
}

void GameObjectCollider::SetPosPointer(Vector3* pPos)
{
	//nullチェック
	assert(pPos);

	pPos_ = pPos;
}

void GameObjectCollider::SetIsSlip(const bool isSlip)
{
	isSlip_ = isSlip;
}
