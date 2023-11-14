#include "CollisionInfoQueue.h"
#include <cassert>

using YGame::CollisionInfo;
using YGame::CollisionInfoQueue;

CollisionInfoQueue* CollisionInfoQueue::GetInstance()
{
	static CollisionInfoQueue instance;
	return &instance;
}

void CollisionInfoQueue::Initialize()
{
	// 空になるまですべての中身を出す
	for (size_t i = 0; i < collQueues_.size(); i++)
	{
		while (true)
		{
			if (collQueues_[i].empty()) { break; }

			collQueues_[i].pop();
		}
	}
}

void CollisionInfoQueue::Update()
{
	// 毎フレームクリア
	Initialize();
}

void CollisionInfoQueue::PushBack(const size_t index, const CollisionInfo& info)
{
	assert(0 <= index && index < collQueues_.size());

	collQueues_[index].push(info);
}

CollisionInfo YGame::CollisionInfoQueue::Front(const size_t index)
{
	assert(0 <= index && index < collQueues_.size());

	return collQueues_[index].front();
}

void CollisionInfoQueue::Pop(const size_t index)
{
	assert(0 <= index && index < collQueues_.size());

	collQueues_[index].pop();
}

bool CollisionInfoQueue::Empty(const size_t index) const
{
	assert(0 <= index && index < collQueues_.size());

	return collQueues_[index].empty();
}
