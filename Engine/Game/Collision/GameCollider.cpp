#include "GameCollider.h"
#include <cassert>

using YGame::GameCollider;
using YGame::InfoOnCollision;
using YMath::BasePrimitiveCollider;
using YMath::Vector3;
using YMath::BitFrag;

std::unique_ptr<GameCollider> GameCollider::Create(const BitFrag& attribute)
{
	std::unique_ptr<GameCollider> newCollider = std::make_unique<GameCollider>();

	newCollider->Initialize(attribute);

	return std::move(newCollider);
}

void GameCollider::ClearCollisionInfoQueue()
{
	// 空になるまですべての中身を出す
	while (true)
	{
		if (infoQueue_.empty()) { break; }

		infoQueue_.pop();
	}
}

void GameCollider::Initialize(const BitFrag& attribute)
{
	if (partColliders_.empty() == false)
	{
		partColliders_.clear();
	}

	ClearCollisionInfoQueue();

	attribute_ = attribute;
}

void GameCollider::Update()
{
	ClearCollisionInfoQueue();
}

bool GameCollider::CheckCollision(GameCollider* pOther)
{
	if (pOther == nullptr) { return false; }

	if (isSlip_ || pOther->IsSlip()) { return false; }

	// 当たった回数をカウント → 1以上ならアタリ
	uint32_t collCounter = 0;

	// 互いに全部位チェック
	for (PartCollider& colliderA : partColliders_)
	{
		for (const PartCollider& colliderB : pOther->partColliders_)
		{
			// 属性とマスク一致しないなら弾く
			if (colliderA.mask_.AND(pOther->attribute_) == false ||
				colliderB.mask_.AND(attribute_) == false)
			{
				continue;
			}

			if (colliderA.primitive_->CheckCollision(*colliderB.primitive_))
			{
				collCounter += 1;
			}
		}
	}

	return (0 < collCounter);
}

void GameCollider::PushBackCollider(
	std::unique_ptr<BasePrimitiveCollider>&& collider, const BitFrag& mask)
{
	assert(collider);
	partColliders_.push_back({});

	auto itr = partColliders_.end();
	itr--;

	itr->mask_ = mask;
	itr->primitive_ = std::move(collider);
}

void GameCollider::PushBackCollisionInfo(InfoOnCollision&& info)
{
	infoQueue_.push(info);
}

std::queue<InfoOnCollision> GameCollider::InfoOnCollisionQueue() const
{
	return infoQueue_;
}

void GameCollider::DrawDebugTextContent()
{

}