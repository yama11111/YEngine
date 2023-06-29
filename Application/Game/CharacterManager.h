#pragma once
#include "ICharacter.h"

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
		void PushBack(ICharacter* character);

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
		static void CheckCollisionCharacterPair(ICharacter* pCharacterA, ICharacter* pCharacterB);
		
		/// <summary>
		/// アタリ判定チェック
		/// </summary>
		/// <param name="pColliderA"> : コライダーA</param>
		/// <param name="pColliderB"> : コライダーB</param>
		static bool CheckCollision(BaseCollider* pColliderA, BaseCollider* pColliderB);

	private:

		// オブジェクトリスト
		std::list<std::unique_ptr<ICharacter>> characters_;

	};
}
