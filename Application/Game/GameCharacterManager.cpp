#include "GameCharacterManager.h"
#include <cassert>

using YGame::GameCharacterManager;

void GameCharacterManager::Initialize()
{
	Clear();
	collMan_.Initialize();
}

void GameCharacterManager::Update()
{
	// オブジェクトnullなら削除
	characters_.remove_if([](std::unique_ptr<IGameCharacter>& character) { return character->IsAlive(); });

	for (std::unique_ptr<IGameCharacter>& character : characters_)
	{
		// 判定前更新
		character->Update();

		// アタリ判定マネージャーに積む
		collMan_.PushBack(character.get());
	}

	// アタリ判定マネージャーを更新
	collMan_.Update();
}

void GameCharacterManager::Draw()
{
	for (std::unique_ptr<IGameCharacter>& character : characters_)
	{
		// 描画
		character->Draw();
	}
}

void GameCharacterManager::Clear()
{
	// オブジェクト全削除
	if (characters_.empty() == false)
	{
		characters_.clear();
	}
}

void GameCharacterManager::PushBack(IGameCharacter* character)
{
	// nullチェック
	assert(character);

	// 新規キャラクター
	std::unique_ptr<IGameCharacter> newCharacter;
	
	// キャラクターリセット
	newCharacter.reset(character);

	// 挿入
	characters_.push_back(std::move(newCharacter));
}
