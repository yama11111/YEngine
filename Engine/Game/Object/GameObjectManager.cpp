#include "GameObjectManager.h"
#include "ViewProjectionManager.h"

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
	// 全削除
	objects_.clear();
	backObjects_.clear();

	updateQueues_.clear();
	collLists_.clear();
	drawQueues_.clear();
}

void GameObjectManager::Initialize()
{
	Clear();
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

void GameObjectManager::Prepare(const bool isContorolUpdate)
{
	// オブジェクトが存在しないなら削除
	objects_.remove_if([](GameObjectSet& object) { return object.obj->IsExist() == false; });
	backObjects_.remove_if([](GameObjectSetForBack& object) { return object.obj->IsExist() == false; });
	
	// 更新キュー
	for (auto itr = updateQueues_.begin(); itr != updateQueues_.end(); ++itr)
	{
		itr->second = UpdateQueue();
	}
	// 判定リスト
	for (auto itr = collLists_.begin(); itr != collLists_.end(); ++itr)
	{
		itr->second = std::list<CollSet>();
	}
	// 描画キュー
	for (auto itr = drawQueues_.begin(); itr != drawQueues_.end(); ++itr)
	{
		itr->second = std::queue<std::function<void()>>();
	}

	// オブジェクト
	for (GameObjectSet& object : objects_)
	{
		object.obj->SetIsControlUpdate(isContorolUpdate);

		if (object.isUpdateSkip)
		{
			object.isSkip = !InUpdateRange(
				object.obj->WorldPos(), object.obj->TransformPtr()->scale_, kUpdateRange,
				ViewProjectionManager::GetInstance()->ViewProjectionPtr(object.obj->UpdateKey()));
		}

		if (object.isSkip) { continue; }

		// キュー、リストに詰める
		updateQueues_[object.obj->UpdateKey()].before.push([&]() { return object.obj->UpdateBeforeCollision(); });
		updateQueues_[object.obj->UpdateKey()].after.push([&]() { return object.obj->UpdateAfterCollision(); });
		
		collLists_[object.obj->UpdateKey()].push_back({ object.obj.get() });
		
		for (size_t i = 0; i < object.obj->DrawKeys().size(); i++)
		{
			drawQueues_[object.obj->DrawKeys()[i]].push([&]() { return object.obj->Draw(); });
		}
	}

	// 背景オブジェクト
	for (GameObjectSetForBack& object : backObjects_)
	{
		object.isSkip = !InUpdateRange(
			object.obj->WorldPos(), object.obj->TransformPtr()->scale_, kUpdateRangeForBack,
			ViewProjectionManager::GetInstance()->ViewProjectionPtr(object.obj->UpdateKey()));

		if (object.isSkip) { continue; }

		// キューに詰める
		updateQueues_[object.obj->UpdateKey()].before.push([&]() { return object.obj->UpdateBeforeCollision(); });
		updateQueues_[object.obj->UpdateKey()].after.push([&]() { return object.obj->UpdateAfterCollision(); });
		for (size_t i = 0; i < object.obj->DrawKeys().size(); i++)
		{
			drawQueues_[object.obj->DrawKeys()[i]].push([&]() { return object.obj->Draw(); });
		}
	}
}

void GameObjectManager::Update(const std::vector<std::string>& updateKeys)
{
	for (size_t i = 0; i < updateKeys.size(); i++)
	{
		if (updateQueues_.contains(updateKeys[i]) == false) { continue; }

		while (true)
		{
			// 空になったら終了
			if (updateQueues_[updateKeys[i]].before.empty()) { break; }

			// 上から順に更新
			updateQueues_[updateKeys[i]].before.front()();
			updateQueues_[updateKeys[i]].before.pop();
		}

		// 全キャラアタリ判定チェック
		CheckAllCollision(updateKeys[i]);

		while (true)
		{
			// 空になったら終了
			if (updateQueues_[updateKeys[i]].after.empty()) { break; }

			// 上から順に更新
			updateQueues_[updateKeys[i]].after.front()();
			updateQueues_[updateKeys[i]].after.pop();
		}
	}
}

bool GameObjectManager::InUpdateRange(
	const YMath::Vector3& pos, const YMath::Vector3& scale, const float range, const ViewProjection* pVP)
{
	// カメラに近いオブジェクト端の位置を求める
	float sign = -1.0f;
	if (pos.x <= pVP->eye_.x) { sign = 1.0f; }
	float basePos = pos.x + sign * (scale.x / 2.0f);

	// 視点との距離
	float distance = std::abs(pVP->eye_.x - basePos);

	return distance <= range;
}

void GameObjectManager::CheckAllCollision(const std::string& key)
{
	// Aの始めから
	std::list<CollSet>::iterator itrA = collLists_[key].begin();

	// Aの終わりまで
	for (; itrA != collLists_[key].end(); ++itrA)
	{
		GameObject* pObjA = itrA->pObj;
		bool isSaveA = itrA->pObj->IsSaveColl();

		// Bの初め(A + 1)から
		std::list<CollSet>::iterator itrB = itrA;
		itrB++;

		// Bの終わりまで
		for (; itrB != collLists_[key].end(); ++itrB)
		{
			GameObject* pObjB = itrB->pObj;
			bool isSaveB = itrA->pObj->IsSaveColl();

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


void GameObjectManager::Draw(const std::vector<std::string>& drawKeys)
{
	for (size_t i = 0; i < drawKeys.size(); i++)
	{
		if (drawQueues_.contains(drawKeys[i]) == false) { continue; }

		while (true)
		{
			// 空になったら終了
			if (drawQueues_[drawKeys[i]].empty()) { break; }

			drawQueues_[drawKeys[i]].front()();
			drawQueues_[drawKeys[i]].pop();
		}
	}
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