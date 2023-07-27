#pragma once
#include "BaseCharacter.h"
#include <queue>

namespace YGame
{
	class CharacterManager
	{
		
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();
		
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
		/// <param name="character"> : キャラクター (動的)</param>
		void PushBack(BaseCharacter* character);

	public:

		/// <summary>
		/// シングルトン
		/// </summary>
		/// <returns></returns>
		static CharacterManager* GetInstance();

	private:

		CharacterManager() = default;

		~CharacterManager() = default;

		CharacterManager(const CharacterManager&) = delete;

		const CharacterManager& operator=(const CharacterManager&) = delete;


	private:

		/// <summary>
		/// アタリ判定全チェック
		/// </summary>
		void CheckAllCollision();

		/// <summary>
		/// ペアのアタリ判定チェック
		/// </summary>
		/// <param name="pCharacterA"> : キャラA</param>
		/// <param name="pCharacterB"> : キャラB</param>
		static void CheckCollisionCharacterPair(BaseCharacter* pCharacterA, BaseCharacter* pCharacterB);

	private:

		// オブジェクトリスト
		std::list<std::unique_ptr<BaseCharacter>> characters_;

	public:

		struct CharaUpdateStatus
		{
			BaseCharacter* pChara_ = nullptr;

			uint16_t priority_ = 0;
		};
	
	private:

		// キャラクター更新処理キュー (優先順位付き : 順)
		std::priority_queue<CharaUpdateStatus> updateQueue_;
	};
	
	inline bool operator< (const CharacterManager::CharaUpdateStatus& status1, const CharacterManager::CharaUpdateStatus& status2)
	{
		return status1.priority_ < status2.priority_;
	}
	inline bool operator> (const CharacterManager::CharaUpdateStatus& status1, const CharacterManager::CharaUpdateStatus& status2)
	{
		return status1.priority_ > status2.priority_;
	}
}
