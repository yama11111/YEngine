#include "CharacterManager.h"
#include <cassert>
#include <imgui.h>

using YGame::CharacterManager;

void CharacterManager::Initialize()
{
	Clear();
}

void CharacterManager::Update()
{
	// キャラクターが死んだら削除
	characters_.remove_if([](std::unique_ptr<ICharacter>& character) { return character->IsAlive() == false; });

	for (std::unique_ptr<ICharacter>& character : characters_)
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
		updateQueue_.top().pChara_->Update();

		updateQueue_.pop();
	}

	// 全キャラアタリ判定チェック
	CheckAllCollision();
}

void CharacterManager::DrawDebugText()
{
	static const std::string windowName = "Game";

	ImGui::SetWindowPos(windowName.c_str(), ImVec2(20.0f, 20.0f), ImGuiCond_Once);
	ImGui::SetWindowSize(windowName.c_str(), ImVec2(240.0f, 680.0f), ImGuiCond_Once);

	ImGui::Begin(windowName.c_str());

	for (std::unique_ptr<ICharacter>& character : characters_)
	{
		character->DrawDebugText(false);
	}
	
	ImGui::End();
}

void CharacterManager::Draw()
{
	for (std::unique_ptr<ICharacter>& character : characters_)
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

void CharacterManager::PushBack(ICharacter* character)
{
	// nullチェック
	assert(character);

	// 新規キャラクター受け取り用
	std::unique_ptr<ICharacter> newCharacter;
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
	std::list<std::unique_ptr<ICharacter>>::iterator itrA = characters_.begin();

	// Aの終わりまで
	for (; itrA != characters_.end(); ++itrA)
	{
		ICharacter* pCharaA = itrA->get();

		// Bの初め(A + 1)から
		std::list<std::unique_ptr<ICharacter>>::iterator itrB = itrA;
		itrB++;

		// Bの終わりまで
		for (; itrB != characters_.end(); ++itrB)
		{
			ICharacter* pCharaB = itrB->get();

			// 判定チェック
			CheckCollisionCharacterPair(pCharaA, pCharaB);
		}
	}
}

void CharacterManager::CheckCollisionCharacterPair(ICharacter* pCharacterA, ICharacter* pCharacterB)
{
	// 判定
	if (pCharacterA->ColliderPtr()->CheckCollision(pCharacterB->ColliderPtr()))
	{
		// お互いに衝突時判定
		pCharacterA->OnCollision(pCharacterB->GetCollisionInfo());
		pCharacterB->OnCollision(pCharacterA->GetCollisionInfo());
	}
}

