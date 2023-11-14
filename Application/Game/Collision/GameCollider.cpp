#include "GameCollider.h"
#include <cassert>

using YGame::GameCollider;
using YMath::BasePrimitiveCollider;
using YMath::Vector3;

void GameCollider::Initialize()
{
	if (colliders_.empty() == false)
	{
		colliders_.clear();
	}
}

bool GameCollider::CheckCollision(GameCollider* pOther)
{
	if (pOther == nullptr) { return false; }
	
	if (isSlip_ || pOther->IsSlip()) { return false; }

	// 当たった回数をカウント → 1以上ならアタリ
	uint32_t collCounter = 0;

	// 互いに全部位チェック
	for (std::unique_ptr<ColliderSet>& colliderA : colliders_)
	{
		for (const std::unique_ptr<ColliderSet>& colliderB : pOther->Colliders())
		{
			// 属性とマスク一致しないなら弾く
			if ((static_cast<uint32_t>(colliderA->attribute) & static_cast<uint32_t>(colliderB->mask)) == 0 ||
				(static_cast<uint32_t>(colliderB->attribute) & static_cast<uint32_t>(colliderA->mask)) == 0)
			{
				continue;
			}
			
			if (colliderA->collider->CheckCollision(*colliderB->collider))
			{
				collCounter += 1;
			}
		}
	}

	return (0 < collCounter);
}

void GameCollider::PushBack(const AttributeType attribute, const AttributeType mask, YMath::BasePrimitiveCollider* collider)
{
	assert(collider);

	std::unique_ptr<ColliderSet> colliderSet = std::make_unique<ColliderSet>();
	
	colliderSet->mask = mask;
	colliderSet->attribute = attribute;
	colliderSet->collider.reset(collider);

	colliders_.push_back(std::move(colliderSet));
}

void GameCollider::DrawDebugTextContent()
{

}

