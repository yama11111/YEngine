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

void GameObjectManager::PushBack(
	std::unique_ptr<GameObject>&& object, 
	const uint32_t updatePriority, 
	const bool isUpdateSkip,
	const bool isSaveCollInfo)
{
	assert(object);

	// 末尾に追加 + イテレーター取得
	// イテレータに情報代入
	objects_.push_back({});
	std::list<GameObjectSet>::iterator itr = objects_.end();
	itr--;
	itr->obj = std::move(object);
	itr->updatePriority = updatePriority;
	itr->isUpdateSkip = isUpdateSkip;
	itr->isSkip = false;
	itr->isSaveCollInfo = isSaveCollInfo;
}

void GameObjectManager::PushBackForBackObject(std::unique_ptr<GameObject>&& object)
{
	assert(object);
	
	// 末尾に追加 + イテレーター取得
	// イテレータに情報代入
	backObjects_.push_back({});
	std::list<GameObjectSetForBack>::iterator itr = backObjects_.end();
	itr--;
	itr->obj = std::move(object);
}

void GameObjectManager::Update(const bool isContorolUpdate)
{
	UpdateObjects(isContorolUpdate);
	
	UpdateObjectsForBack();
}

void GameObjectManager::UpdateObjects(const bool isContorolUpdate)
{
	// オブジェクトが存在しないなら削除
	objects_.remove_if([](GameObjectSet& object) { return object.obj->IsExist() == false; });

	// 更新処理用キュー
	std::priority_queue<GameObjectSet*> updateBeforeCollQueue, updateAfterCollQueue;

	for (GameObjectSet& object : objects_)
	{
		object.obj->SetIsControlUpdate(isContorolUpdate);

		if (object.isUpdateSkip)
		{
			object.isSkip = (InUpdateRange(object.obj.get()) == false);
		}

		if (object.isSkip == false)
		{
			updateBeforeCollQueue.push({ &object });
			updateAfterCollQueue.push({ &object });
		}
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

void GameObjectManager::UpdateObjectsForBack()
{
	for (GameObjectSetForBack& object : backObjects_)
	{
		object.isSkip = (InUpdateRangeForBack(object.obj.get()) == false);

		if (object.isSkip == false)
		{
			object.obj->UpdateBeforeCollision();
			object.obj->UpdateAfterCollision();
		}
	}
}

bool GameObjectManager::InUpdateRange(GameObject* pObject)
{
	// 視点との距離
	float distance = YMath::Vector3(pVP_->eye_ - pObject->TransformPtr()->pos_).Length();

	// 更新範囲
	static const float kUpdateRange = 250.0f;

	return distance <= kUpdateRange;
}

bool GameObjectManager::InUpdateRangeForBack(GameObject* pObject)
{
	// 視点との距離
	float distance = YMath::Vector3(pVP_->eye_ - pObject->TransformPtr()->pos_).Length();

	// 更新範囲
	static const float kUpdateRange = 500.0f;

	return distance <= kUpdateRange;
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

		// Bの初め(A + 1)から
		std::list<GameObjectSet>::iterator itrB = itrA;
		itrB++;

		// Bの終わりまで
		for (; itrB != objects_.end(); ++itrB)
		{
			if (itrB->isSkip) { continue; }
			
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
	if (isColl)
	{
		// お互いに衝突時判定
		if (isSaveB) { pCollA->PushBackCollisionInfo(pObjectB->GetInfoOnCollision()); }
		if (isSaveA) { pCollB->PushBackCollisionInfo(pObjectA->GetInfoOnCollision()); }
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

void GameObjectManager::Draw()
{
	for (GameObjectSetForBack& object : backObjects_)
	{
		if (object.isSkip) { continue; }
		object.obj->Draw();
	}

	int a = 0;
	for (GameObjectSet& object : objects_)
	{
		if(object.obj->Name() == "Life")
		{
			a++;
		}
		if (object.isSkip) { continue; }
		object.obj->Draw();
	}
}
