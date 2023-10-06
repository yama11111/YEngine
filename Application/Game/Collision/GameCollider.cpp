#include "GameCollider.h"
#include "PrimitiveCollider.h"
#include <cassert>

using YGame::GameCollider;
using YMath::BasePrimitiveCollider;
using YMath::Vector3;

GameCollider::GameCollider(
	Transform* pParent, 
	const AttributeType attribute, const AttributeType mask,
	const bool isSlip) :
	pParent_(nullptr), attribute_(attribute), mask_(mask), isSlip_(isSlip)
{
}

void GameCollider::Initialize(
	Transform* pParent, 
	const AttributeType attribute, const AttributeType mask, 
	const bool isSlip, const bool isClear)
{
	pParent_ = pParent;
	attribute_ = attribute;
	mask_ = mask;
	isSlip_ = isSlip;

	if (isClear && colliders_.empty() == false)
	{
		colliders_.clear();
	}
}

bool GameCollider::CheckCollision(GameCollider* pOther)
{
	if (pOther == nullptr) { return false; }

	// どちらかすり抜けるなら弾く
	if (isSlip_ || pOther->IsSlip()) { return false; }

	// 属性とマスク一致しないなら弾く
	if ((static_cast<uint32_t>(attribute_) & static_cast<uint32_t>(pOther->Mask())) == 0 ||
		(static_cast<uint32_t>(pOther->Attribute()) & static_cast<uint32_t>(mask_)) == 0)
	{
		return false;
	}

	// 互いに全部位チェック
	for (std::unique_ptr<BasePrimitiveCollider>& colliderA : colliders_)
	{
		for (const std::unique_ptr<BasePrimitiveCollider>& colliderB : pOther->Colliders())
		{
			// 1つでも当たったらtrue
			if (colliderA->CheckCollision(*colliderB))
			{
				return true;
			}
		}
	}

	return false;
}

void GameCollider::PushBack(BasePrimitiveCollider* collider)
{
	std::unique_ptr<BasePrimitiveCollider> newCollider;
	
	newCollider.reset(collider);

	if (pParent_)
	{
		// 追従点挿入
		newCollider->SetFollowPoint(&pParent_->pos_);
	}

	colliders_.push_back(std::move(newCollider));
}

void GameCollider::DrawDebugTextContent()
{

}

