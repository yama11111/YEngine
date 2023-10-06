#include "CharacterManager.h"
#include <cassert>
#include <imgui.h>

#include "AxisDrawer.h"
#include "CollisionDrawer.h"

using YGame::CharacterManager;

void CharacterManager::Initialize()
{
	Clear();
}

void CharacterManager::Update(const bool isUpdate)
{
	// キャラクターが死んだら削除
	characters_.remove_if([](std::unique_ptr<BaseCharacter>& character) { return character->IsAlive() == false; });

	for (std::unique_ptr<BaseCharacter>& character : characters_)
	{
		uint16_t priority = 0;
		if (character->ColliderPtr()->Attribute() == AttributeType::ePet)
		{
			priority = 1;
		}

		updateQueue_.push({ character.get(), priority });
	}

	while (true)
	{		
		// 空になったら終了
		if (updateQueue_.empty()) { break; }

		// 上から順に更新
		updateQueue_.top().pChara_->Update(isUpdate);

		updateQueue_.pop();
	}

	// 全キャラアタリ判定チェック
	CheckAllCollision();
}

void CharacterManager::DrawDebugText()
{
	static const std::string windowName = "Character";

	ImGui::SetWindowPos(windowName.c_str(), ImVec2(20.0f, 20.0f), ImGuiCond_Once);
	ImGui::SetWindowSize(windowName.c_str(), ImVec2(240.0f, 680.0f), ImGuiCond_Once);

	ImGui::Begin(windowName.c_str());

	for (std::unique_ptr<BaseCharacter>& character : characters_)
	{
		character->DrawDebugText(false);
	}
	
	ImGui::End();

	ImGui::Begin("DebugDraw");
	ImGui::Checkbox("Axis", &isDrawAxis_);
	ImGui::Checkbox("Collision", &isDrawCollision_);
	ImGui::End();

	for (std::unique_ptr<BaseCharacter>& character : characters_)
	{
		character->SubDrawerPtr(AxisDrawer::Name())->SetIsVisible(isDrawAxis_);
		character->SubDrawerPtr(CollisionDrawer::Name())->SetIsVisible(isDrawCollision_);
	}
}

void CharacterManager::Draw()
{
	for (std::unique_ptr<BaseCharacter>& character : characters_)
	{
		character->Draw();
	}
}

void CharacterManager::Clear()
{
	if (characters_.empty() == false)
	{
		// 全削除
		characters_.clear();
	}
}

void CharacterManager::PushBack(BaseCharacter* character)
{
	// nullチェック
	assert(character);

	// 新規キャラクター受け取り用
	std::unique_ptr<BaseCharacter> newCharacter;
	newCharacter.reset(character);

	// 挿入
	characters_.push_back(std::move(newCharacter));
}

CharacterManager* CharacterManager::GetInstance()
{
	static CharacterManager instance;
	return &instance;
}

void CharacterManager::CheckAllCollision()
{
	// Aの始めから
	std::list<std::unique_ptr<BaseCharacter>>::iterator itrA = characters_.begin();

	// Aの終わりまで
	for (; itrA != characters_.end(); ++itrA)
	{
		BaseCharacter* pCharaA = itrA->get();

		// Bの初め(A + 1)から
		std::list<std::unique_ptr<BaseCharacter>>::iterator itrB = itrA;
		itrB++;

		// Bの終わりまで
		for (; itrB != characters_.end(); ++itrB)
		{
			BaseCharacter* pCharaB = itrB->get();

			// 判定チェック
			CheckCollisionCharacterPair(pCharaA, pCharaB);
		}
	}
}

void CharacterManager::CheckCollisionCharacterPair(BaseCharacter* pCharacterA, BaseCharacter* pCharacterB)
{
	// 判定
	if (pCharacterA->ColliderPtr()->CheckCollision(pCharacterB->ColliderPtr()))
	{
		// お互いに衝突時判定
		pCharacterA->OnCollision(pCharacterB->GetCollisionInfo());
		pCharacterB->OnCollision(pCharacterA->GetCollisionInfo());
	}
}

