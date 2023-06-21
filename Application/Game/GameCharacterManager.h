#pragma once
#include "IGameCharacter.h"

namespace YGame
{
	class GameCharacterManager
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
		void PushBack(IGameCharacter* character);

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
		static void CheckCollisionPair(IGameCharacter* pCharacterA, IGameCharacter* pCharacterB);

	private:

		// オブジェクトリスト
		std::list<std::unique_ptr<IGameCharacter>> characters_;

	};
}
