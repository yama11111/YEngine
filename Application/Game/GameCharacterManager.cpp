#include "GameCharacterManager.h"
#include <cassert>

using YGame::GameCharacterManager;

void GameCharacterManager::Initialize()
{
	Clear();
}

void GameCharacterManager::Update()
{
	// オブジェクトnullなら削除
	characters_.remove_if([](std::unique_ptr<IGameCharacter>& character) { return character->IsAlive(); });

	// 全キャラクター
	for (std::unique_ptr<IGameCharacter>& character : characters_)
	{
		// 判定前更新
		character->Update();
	}

	// アタリ判定全チェック
	CheckAllCollision();
}

void GameCharacterManager::Draw()
{
	// 全キャラクター
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

void GameCharacterManager::CheckAllCollision()
{
	// Aの始めから
	std::list<std::unique_ptr<IGameCharacter>>::iterator itrA = characters_.begin();

	// Aの終わりまで
	for (; itrA != characters_.end(); ++itrA)
	{
		// ポインタを取得
		IGameCharacter* pCharaA = itrA->get();

		// Bの初め(A + 1)から
		std::list<std::unique_ptr<IGameCharacter>>::iterator itrB = itrA;
		itrB++;

		// Bの終わりまで
		for (; itrB != characters_.end(); ++itrB)
		{
			// ポインタを取得
			IGameCharacter* pCharaB = itrB->get();

			// 判定チェック
			CheckCollisionPair(pCharaA, pCharaB);
		}
	}
}

void GameCharacterManager::CheckCollisionPair(IGameCharacter* pCharacterA, IGameCharacter* pCharacterB)
{
	// どちらかすり抜けるなら弾く
	if (pCharacterA->IsSlip() || pCharacterB->IsSlip()) { return; }

	// 属性とマスク一致しないなら弾く
	if ((pCharacterA->Attribute() & pCharacterB->Mask()) == 0 || 
		(pCharacterB->Attribute() & pCharacterA->Mask()) == 0) 
	{
		return;
	}

	// 球 と 球 の判定
	if (YGame::CollisionSphereSphere(*pCharacterA, *pCharacterB))
	{
		// お互いに衝突時判定
		pCharacterA->OnCollision(pCharacterB);
		pCharacterB->OnCollision(pCharacterA);
	}
}
