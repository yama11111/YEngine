#pragma once
#include "GameObject.h"
#include "CollisionInfoQueue.h"
#include <queue>

namespace YGame
{
	class GameObjectManager
	{
		
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="isUpdate"> : 更新するか</param>
		void Update(const bool isUpdate);
		
		/// <summary>
		/// デバッグ描画
		/// </summary>
		void DrawDebugText();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

	public:

		/// <summary>
		/// クリア
		/// </summary>
		void Clear();

		/// <summary>
		/// 挿入
		/// </summary>
		/// <param name="object"> : オブジェクト (動的)</param>
		/// <param name="updatePriority"> : 更新優先度</param>
		/// <param name="isSaveCollInfo"> : 衝突情報を保存するか</param>
		void PushBack(GameObject* object, const uint32_t updatePriority, const bool isSaveCollInfo);

	public:

		/// <summary>
		/// シングルトン
		/// </summary>
		/// <returns></returns>
		static GameObjectManager* GetInstance();

	public:

		// オブジェクト構造体
		struct GameObjectSet
		{
			// 本体
			std::unique_ptr<GameObject> obj;

			// 優先度
			uint32_t updatePriority;

			// 衝突情報を保存するか
			bool isSaveCollInfo;
		};

	private:

		// オブジェクトリスト
		std::list<GameObjectSet> objects_;

		// 軸描画フラグ
		bool isDrawAxis_ = false;

		// アタリ判定描画フラグ
		bool isDrawCollision_ = false;

		// 衝突情報キューポインタ
		CollisionInfoQueue* pCollisionInfoQueue_ = nullptr;

	private:

		GameObjectManager() = default;
		~GameObjectManager() = default;
		GameObjectManager(const GameObjectManager&) = delete;
		const GameObjectManager& operator=(const GameObjectManager&) = delete;

	private:

		/// <summary>
		/// アタリ判定全チェック
		/// </summary>
		void CheckAllCollision();

		/// <summary>
		/// ペアのアタリ判定チェック
		/// </summary>
		/// <param name="pObjectA"> : オブジェクトA</param>
		/// <param name="isSaveA"> : 保存フラグA</param>
		/// <param name="pObjectB"> : オブジェクトB</param>
		/// <param name="isSaveB"> : 保存フラグB</param>
		static void CheckCollisionCharacterPair(
			GameObject* pObjectA, const bool isSaveA,
			GameObject* pObjectB, const bool isSaveB);
	};
	
	inline bool operator< (const GameObjectManager::GameObjectSet& objectSet1, const GameObjectManager::GameObjectSet& objectSet2)
	{
		return objectSet1.updatePriority < objectSet2.updatePriority;
	}
	inline bool operator> (const GameObjectManager::GameObjectSet& objectSet1, const GameObjectManager::GameObjectSet& objectSet2)
	{
		return objectSet1.updatePriority > objectSet2.updatePriority;
	}
}
