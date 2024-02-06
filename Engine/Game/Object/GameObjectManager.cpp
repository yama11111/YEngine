#include "GameObjectManager.h"

#include "AxisDrawer.h"
#include "CollisionDrawer.h"

#include <cassert>
#include <cmath>
#include <imgui.h>

using YGame::GameObjectManager;

namespace 
{
	// 更新範囲
	const float kUpdateRange = 100.0f;
	const float kUpdateRangeForBack = 500.0f;
}

GameObjectManager* GameObjectManager::GetInstance()
{
	static GameObjectManager instance;
	return &instance;
}

void GameObjectManager::Clear()
{
	if (objects_.empty() == false)
	{
		// 全削除
		objects_.clear();
	}

	if (backObjects_.empty() == false)
	{
		// 全削除
		backObjects_.clear();
	}
}

void GameObjectManager::Initialize(ViewProjection* pVP)
{
	assert(pVP);

	Clear();

	pVP_ = pVP;
}

void GameObjectManager::PushBack(std::unique_ptr<GameObject>&& object, const bool isUpdateSkip)
{
	assert(object);

	// 末尾に追加 + イテレーター取得
	// イテレータに情報代入
	objects_.push_back({ std::move(object), isUpdateSkip, false });
}

void GameObjectManager::PushBackForBackObject(std::unique_ptr<GameObject>&& object)
{
	assert(object);
	
	// 末尾に追加 + イテレーター取得
	// イテレータに情報代入
	backObjects_.push_back({ std::move(object) });
}

void GameObjectManager::Update(const bool isContorolUpdate)
{
	// オブジェクトが存在しないなら削除
	objects_.remove_if([](GameObjectSet& object) { return object.obj->IsExist() == false; });
	backObjects_.remove_if([](GameObjectSetForBack& object) { return object.obj->IsExist() == false; });
	
	// 描画キュー
	for (auto itr = drawQueues_.begin(); itr != drawQueues_.end(); ++itr)
	{
		itr->second = std::queue<std::function<void()>>();
	}

	UpdateObjects(isContorolUpdate);
	UpdateObjectsForBack();
}

void GameObjectManager::UpdateObjects(const bool isContorolUpdate)
{
	// 更新処理用キュー
	std::queue<std::function<void()>> beforeQueue, afterQueue;

	for (GameObjectSet& object : objects_)
	{
		object.obj->SetIsControlUpdate(isContorolUpdate);

		if (object.isUpdateSkip)
		{
			object.isSkip = (InUpdateRange(
				object.obj->WorldPos(), 
				object.obj->TransformPtr()->scale_,
				kUpdateRange) == false);
		}
		
		if (object.isSkip) { continue; }

		// キューに詰める
		beforeQueue.push([&]() { return object.obj->UpdateBeforeCollision(); });
		afterQueue.push([&]() { return object.obj->UpdateAfterCollision(); });
		for (size_t i = 0; i < object.obj->DrawKeys().size(); i++)
		{
			drawQueues_[object.obj->DrawKeys()[i]].push([&]() { return object.obj->Draw(); });
		}
	}

	// 前更新
	while (true)
	{
		// 空になったら終了
		if (beforeQueue.empty()) { break; }

		// 上から順に更新
		beforeQueue.front()();
		beforeQueue.pop();
	}

	// 全キャラアタリ判定チェック
	CheckAllCollision();

	// 後更新
	while (true)
	{
		// 空になったら終了
		if (afterQueue.empty()) { break; }

		// 上から順に更新
		afterQueue.front()();
		afterQueue.pop();
	}
}

void GameObjectManager::UpdateObjectsForBack()
{
	for (GameObjectSetForBack& object : backObjects_)
	{
		object.isSkip = (InUpdateRange(
			object.obj->WorldPos(),
			object.obj->TransformPtr()->scale_,
			kUpdateRangeForBack) == false);

		if (object.isSkip) { continue; }
		
		object.obj->UpdateBeforeCollision();
		object.obj->UpdateAfterCollision();

		// キューに詰める
		for (size_t i = 0; i < object.obj->DrawKeys().size(); i++)
		{
			drawQueues_[object.obj->DrawKeys()[i]].push([&]() { return object.obj->Draw(); });
		}
	}
}

bool GameObjectManager::InUpdateRange(const YMath::Vector3& pos, const YMath::Vector3& scale, const float range)
{
	// カメラに近いオブジェクト端の位置を求める
	float sign = -1.0f;
	if (pos.x <= pVP_->eye_.x) { sign = 1.0f; }
	float basePos = pos.x + sign * (scale.x / 2.0f);

	// 視点との距離
	float distance = std::abs(pVP_->eye_.x - basePos);

	return distance <= range;
}

void GameObjectManager::CheckAllCollision()
{
	// Aの始めから
	std::list<GameObjectSet>::iterator itrA = objects_.begin();

	// Aの終わりまで
	for (; itrA != objects_.end(); ++itrA)
	{
		if (itrA->isSkip) { continue; }
		
		GameObject* pObjA = itrA->obj.get();
		bool isSaveA = itrA->obj->IsSaveColl();

		// Bの初め(A + 1)から
		std::list<GameObjectSet>::iterator itrB = itrA;
		itrB++;

		// Bの終わりまで
		for (; itrB != objects_.end(); ++itrB)
		{
			if (itrB->isSkip) { continue; }
			
			GameObject* pObjB = itrB->obj.get();
			bool isSaveB = itrA->obj->IsSaveColl();

			// 判定チェック
			CheckCollisionObjectPair(pObjA, isSaveA, pObjB, isSaveB);
		}
	}
}

void GameObjectManager::CheckCollisionObjectPair(
	GameObject* pObjectA, const bool isSaveA,
	GameObject* pObjectB, const bool isSaveB)
{
	GameCollider* pCollA = pObjectA->ColliderPtr();
	GameCollider* pCollB = pObjectB->ColliderPtr();

	if (pCollA == nullptr || pCollB == nullptr) { return; }

	bool isColl = false;

	if (pCollA->Priority() < pCollB->Priority())
	{
		isColl = pCollB->CheckCollision(pCollA);
	}
	else
	{
		isColl = pCollA->CheckCollision(pCollB);
	}

	// 判定
	if (isColl == false) { return; }
	
	// お互いに衝突時判定
	if (isSaveB) { pCollA->PushBackCollisionInfo(pObjectB->GetInfoOnCollision()); }
	if (isSaveA) { pCollB->PushBackCollisionInfo(pObjectA->GetInfoOnCollision()); }
}

void GameObjectManager::DrawDebugText()
{
	static const std::string windowName = "Character";

	ImGui::SetWindowPos(windowName.c_str(), ImVec2(20.0f, 20.0f), ImGuiCond_Once);
	ImGui::SetWindowSize(windowName.c_str(), ImVec2(240.0f, 680.0f), ImGuiCond_Once);

	ImGui::Begin(windowName.c_str());

	for (GameObjectSet& object : objects_)
	{
		object.obj->DrawDebugText(false);
	}

	ImGui::End();
}

void GameObjectManager::Draw()
{
	for (GameObjectSetForBack& object : backObjects_)
	{
		if (object.isSkip) { continue; }
		object.obj->Draw();
	}

	for (GameObjectSet& object : objects_)
	{
		if (object.isSkip) { continue; }
		object.obj->Draw();
	}
}

void GameObjectManager::Draw(const std::vector<std::string>& drawKeys)
{
	for (size_t i = 0; i < drawKeys.size(); i++)
	{
		if (drawQueues_.contains(drawKeys[i]) == false) { continue; }

		drawQueues_[drawKeys[i]].front()();
		drawQueues_[drawKeys[i]].pop();
	}
}
