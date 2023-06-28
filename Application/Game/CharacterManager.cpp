#include "CharacterManager.h"
#include "SphereCollider.h"
#include <cassert>

using YGame::CharacterManager;

void CharacterManager::Initialize()
{
	Clear();
}

void CharacterManager::Update()
{
	// オブジェクトnullなら削除
	characters_.remove_if([](std::unique_ptr<ICharacter>& character) { return character->IsAlive(); });

	// 全キャラクター
	for (std::unique_ptr<ICharacter>& character : characters_)
	{
		// 判定前更新
		character->Update();
	}

	// アタリ判定全チェック
	CheckAllCollision();
}

void CharacterManager::Draw()
{
	// 全キャラクター
	for (std::unique_ptr<ICharacter>& character : characters_)
	{
		// 描画
		character->Draw();
	}
}

void CharacterManager::Clear()
{
	// オブジェクト全削除
	if (characters_.empty() == false)
	{
		characters_.clear();
	}
}

void CharacterManager::PushBack(ICharacter* character)
{
	// nullチェック
	assert(character);

	// 新規キャラクター
	std::unique_ptr<ICharacter> newCharacter;
	
	// キャラクターリセット
	newCharacter.reset(character);

	// 挿入
	characters_.push_back(std::move(newCharacter));
}

void CharacterManager::CheckAllCollision()
{
	// Aの始めから
	std::list<std::unique_ptr<ICharacter>>::iterator itrA = characters_.begin();

	// Aの終わりまで
	for (; itrA != characters_.end(); ++itrA)
	{
		// ポインタを取得
		ICharacter* pCharaA = itrA->get();

		// Bの初め(A + 1)から
		std::list<std::unique_ptr<ICharacter>>::iterator itrB = itrA;
		itrB++;

		// Bの終わりまで
		for (; itrB != characters_.end(); ++itrB)
		{
			// ポインタを取得
			ICharacter* pCharaB = itrB->get();

			// 判定チェック
			CheckCollisionCharacterPair(pCharaA, pCharaB);
		}
	}
}

void CharacterManager::CheckCollisionCharacterPair(ICharacter* pCharacterA, ICharacter* pCharacterB)
{
	// 球 と 球 の判定
	if (CheckCollision(pCharacterA->ColliderPtr(), pCharacterB->ColliderPtr()))
	{
		// お互いに衝突時判定
		//pCharacterA->OnCollision({});
		//pCharacterB->OnCollision({});
	}
}

bool CharacterManager::CheckCollision(BaseCollider* pColliderA, BaseCollider* pColliderB)
{
	// コライダーが無いなら弾く
	if (pColliderA == nullptr || pColliderB == nullptr)
	{
		return false;
	}

	// どちらかすり抜けるなら弾く
	if (pColliderA->IsSlip() || pColliderB->IsSlip()) 
	{
		return false; 
	}

	// 属性とマスク一致しないなら弾く
	if ((pColliderA->Attribute() & pColliderB->Mask()) == 0 ||
		(pColliderB->Attribute() & pColliderA->Mask()) == 0)
	{
		return false;
	}

	// どちらも球なら
	if (pColliderA->Shape() == BaseCollider::ShapeType::eSphere && 
		pColliderB->Shape() == BaseCollider::ShapeType::eSphere)
	{
		// キャスト
		SphereCollider* pSphereA = static_cast<SphereCollider*>(pColliderA);
		SphereCollider* pSphereB = static_cast<SphereCollider*>(pColliderB);

		// 球 と 球 の判定
		return YGame::CollisionSphereSphere(*pSphereA, *pSphereB);
	}

	return false;
}

