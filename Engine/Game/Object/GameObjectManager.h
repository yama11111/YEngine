/**
 * @file GameObjectManager.h
 * @brief ゲームオブジェクト管理クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "GameObject.h"
#include "ViewProjection.h"
#include <queue>
#include <functional>

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
		/// <param name="isContorolUpdate"> : 操作更新するか</param>
		void Prepare(const bool isContorolUpdate);

		/// <summary>
		/// 更新
		/// </summary>
		void Update(const std::vector<std::string>& updateKeys);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="drawKeys"> : 描画キューのキー</param>
		void Draw(const std::vector<std::string>& drawKeys);
		
		/// <summary>
		/// デバッグ描画
		/// </summary>
		void DrawDebugText();

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
		void PushBack(std::unique_ptr<GameObject>&& object, const bool isUpdateSkip);

		/// <summary>
		/// 挿入
		/// </summary>
		/// <param name="object"> : オブジェクト (動的)</param>
		/// <param name="updatePriority"> : 更新優先度</param>
		void PushBackForBackObject(std::unique_ptr<GameObject>&& object);

	public:

		/// <summary>
		/// 基準位置設定
		/// </summary>
		/// <param name="basePoint"> : 基準位置</param>
		void SetBasePoint(const YMath::Vector3& basePoint);

		/// <summary>
		/// 更新範囲設定
		/// </summary>
		/// <param name="updateRange"> : 更新範囲</param>
		/// <param name="updateRangeForBack"> : 更新範囲(背景)</param>
		void SetUpdateRagne(const float updateRange, const float updateRangeForBack);

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

			// 更新スキップをするか
			bool isUpdateSkip = false;

			// 処理を飛ばすか
			bool isSkip = false;
		};
		
		// オブジェクト構造体
		struct GameObjectSetForBack
		{
			// 本体
			std::unique_ptr<GameObject> obj;

			// 処理を飛ばすか
			bool isSkip = false;
		};

		// 関数
		struct UpdateQueue
		{
			std::queue<std::function<void()>> before;
			std::queue<std::function<void()>> after;
		};

		// 衝突判定セット
		struct CollSet
		{
			GameObject* pObj;
		};

	private:

		// オブジェクトリスト
		std::list<GameObjectSet> objects_;
		
		// 背景オブジェクトリスト
		std::list<GameObjectSetForBack> backObjects_;

		// 更新処理用キューマップ
		std::unordered_map<std::string, UpdateQueue> updateQueueMap_;
		
		// 判定リストマップ
		std::unordered_map<std::string, std::list<CollSet>> collListMap_;

		// 描画処理関数キューマップ
		std::unordered_map<std::string, std::queue<std::function<void()>>> drawQueueMap_;


		// 基準位置
		YMath::Vector3 basePoint_;

		// 更新範囲
		float updateRange_ = 100.0f;

		// 更新範囲(背景)
		float updateRangeForBack_ = 500.0f;

	private:

		/// <summary>
		/// 更新範囲内か
		/// </summary>
		/// <param name="pos"> : 座標</param>
		/// <param name="scale"> : スケール</param>
		/// <param name="range"> : 範囲</param>
		/// <returns>更新範囲内か</returns>
		bool InUpdateRange(
			const YMath::Vector3& pos, 
			const YMath::Vector3& scale, 
			const float range);

		/// <summary>
		/// アタリ判定全チェック
		/// </summary>
		/// <param name="key"> : キー</param>
		void CheckAllCollision(const std::string& key);

		/// <summary>
		/// ペアのアタリ判定チェック
		/// </summary>
		/// <param name="pObjectA"> : オブジェクトA</param>
		/// <param name="isSaveA"> : 保存フラグA</param>
		/// <param name="pObjectB"> : オブジェクトB</param>
		/// <param name="isSaveB"> : 保存フラグB</param>
		static void CheckCollisionObjectPair(
			GameObject* pObjectA, const bool isSaveA,
			GameObject* pObjectB, const bool isSaveB);

	private:

		GameObjectManager() = default;
		~GameObjectManager() = default;
		GameObjectManager(const GameObjectManager&) = delete;
		const GameObjectManager& operator=(const GameObjectManager&) = delete;
	};
}
