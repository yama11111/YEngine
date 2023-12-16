#pragma once
#include "GameObject.h"
#include <queue>

namespace YGame
{
	class GameObjectManager
	{
		
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		void Initialize(ViewProjection* pVP);

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="isContorolUpdate"> : 操作更新するか</param>
		void Update(const bool isContorolUpdate);
		
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
		/// <param name="isUpdateSkip"> : 更新スキップをするか</param>
		/// <param name="isSaveCollInfo"> : 衝突情報を保存するか</param>
		void PushBack(
			std::unique_ptr<GameObject>&& object, 
			const uint32_t updatePriority, 
			const bool isUpdateSkip, 
			const bool isSaveCollInfo);

		/// <summary>
		/// 挿入
		/// </summary>
		/// <param name="object"> : オブジェクト (動的)</param>
		/// <param name="updatePriority"> : 更新優先度</param>
		void PushBackForBackObject(std::unique_ptr<GameObject>&& object);

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

			// 更新スキップをするか
			bool isUpdateSkip = false;

			// 処理を飛ばすか
			bool isSkip = false;

			// 衝突情報を保存するか
			bool isSaveCollInfo = false;
		};
		
		// オブジェクト構造体
		struct GameObjectSetForBack
		{
			// 本体
			std::unique_ptr<GameObject> obj;
			
			// 処理を飛ばすか
			bool isSkip = false;
		};

	private:

		// オブジェクトリスト
		std::list<GameObjectSet> objects_;
		
		// 背景オブジェクトリスト
		std::list<GameObjectSetForBack> backObjects_;

		// 軸描画フラグ
		bool isDrawAxis_ = false;

		// アタリ判定描画フラグ
		bool isDrawCollision_ = false;

		// ビュープロジェクションポインタ
		ViewProjection* pVP_ = nullptr;

	private:

		GameObjectManager() = default;
		~GameObjectManager() = default;
		GameObjectManager(const GameObjectManager&) = delete;
		const GameObjectManager& operator=(const GameObjectManager&) = delete;

	private:

		/// <summary>
		/// オブジェクト更新
		/// </summary>
		void UpdateObjects(const bool isContorolUpdate);
		
		/// <summary>
		/// 背景オブジェクト更新
		/// </summary>
		void UpdateObjectsForBack();

		/// <summary>
		/// 更新範囲内か
		/// </summary>
		/// <param name="pObject"> : オブジェクトポインタ</param>
		/// <returns>更新範囲内か</returns>
		bool InUpdateRange(GameObject* pObject);

		/// <summary>
		/// 更新範囲内か
		/// </summary>
		/// <param name="pObject"> : オブジェクトポインタ</param>
		/// <returns>更新範囲内か</returns>
		bool InUpdateRangeForBack(GameObject* pObject);

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
