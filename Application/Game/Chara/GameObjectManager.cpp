#include "GameObjectManager.h"

#include "AxisDrawer.h"
#include "CollisionDrawer.h"

#include <cassert>
#include <imgui.h>

using YGame::GameObjectManager;

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
}

void GameObjectManager::Initialize()
{
	pCollisionInfoQueue_ = CollisionInfoQueue::GetInstance();

	Clear();
}

void GameObjectManager::Update(const bool isUpdate)
{
	pCollisionInfoQueue_->Update();
	
	// オブジェクトが存在しないなら削除
	objects_.remove_if([](GameObjectSet& object) { return object.obj->IsExist() == false; });
	
	// 更新処理用キュー
	std::priority_queue<GameObjectSet*> updateBeforeCollQueue, updateAfterCollQueue;

	for (GameObjectSet& object : objects_)
	{
		object.obj->SetIsUpdate(isUpdate);
	}

	for (GameObjectSet& object: objects_)
	{
		updateBeforeCollQueue.push({ &object });
		updateAfterCollQueue.push({ &object });
	}

	// 前更新
	while (true)
	{
		// 空になったら終了
		if (updateBeforeCollQueue.empty()) { break; }

		// 上から順に更新
		updateBeforeCollQueue.top()->obj->UpdateBeforeCollision();
		
		updateBeforeCollQueue.pop();
	}

	// 全キャラアタリ判定チェック
	CheckAllCollision();

	// 後更新
	while (true)
	{
		// 空になったら終了
		if (updateAfterCollQueue.empty()) { break; }

		// 上から順に更新
		updateAfterCollQueue.top()->obj->UpdateAfterCollision();

		updateAfterCollQueue.pop();
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

	ImGui::Begin("DebugDraw");
	ImGui::Checkbox("Axis", &isDrawAxis_);
	ImGui::Checkbox("Collision", &isDrawCollision_);
	ImGui::End();

	//for (GameObjectSet& object : objects_)
	//{
	//	object.obj->SubDrawerPtr(AxisDrawer::Name())->SetIsVisible(isDrawAxis_);
	//	object.obj->SubDrawerPtr(CollisionDrawer::Name())->SetIsVisible(isDrawCollision_);
	//}
}

void GameObjectManager::Draw()
{
	for (GameObjectSet& object : objects_)
	{
		object.obj->Draw();
	}
}

void GameObjectManager::PushBack(GameObject* object, const uint32_t updatePriority, const bool isSaveCollInfo)
{
	assert(object);

	// 末尾に追加 + イテレーター取得
	// イテレータに情報代入
	objects_.push_back({});
	std::list<GameObjectSet>::iterator itr = objects_.end();
	itr--;
	itr->obj.reset(object);
	itr->updatePriority = updatePriority;
	itr->isSaveCollInfo = isSaveCollInfo;
}

void GameObjectManager::CheckAllCollision()
{
	size_t index = 0;
	for (GameObjectSet& object : objects_)
	{
		if (object.isSaveCollInfo)
		{
			object.obj->SetCollisionIndex(index);
			index++;
		}
	}

	// Aの始めから
	std::list<GameObjectSet>::iterator itrA = objects_.begin();

	// Aの終わりまで
	for (; itrA != objects_.end(); ++itrA)
	{
		GameObject* pObjA = itrA->obj.get();

		// Bの初め(A + 1)から
		std::list<GameObjectSet>::iterator itrB = itrA;
		itrB++;

		// Bの終わりまで
		for (; itrB != objects_.end(); ++itrB)
		{
			GameObject* pObjB = itrB->obj.get();

			// 判定チェック
			CheckCollisionCharacterPair(pObjA, itrA->isSaveCollInfo, pObjB, itrB->isSaveCollInfo);
		}
	}
}

void GameObjectManager::CheckCollisionCharacterPair(
	GameObject* pObjectA, const bool isSaveA,
	GameObject* pObjectB, const bool isSaveB)
{
	if (pObjectA->ColliderPtr() == nullptr || pObjectB->ColliderPtr() == nullptr) { return; }

	bool isColl = false;

	if (pObjectA->ColliderPtr()->Priority() < pObjectB->ColliderPtr()->Priority())
	{
		isColl = pObjectB->ColliderPtr()->CheckCollision(pObjectA->ColliderPtr()); 
	}
	else 
	{
		isColl = pObjectA->ColliderPtr()->CheckCollision(pObjectB->ColliderPtr());
	}

	// 判定
	if (isColl)
	{
		// お互いに衝突時判定
		if (isSaveB) { pObjectA->SendCollisionInfo(pObjectB->CollisionIndex()); }
		if (isSaveA) { pObjectB->SendCollisionInfo(pObjectA->CollisionIndex()); }
	}
}
