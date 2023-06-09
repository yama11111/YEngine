#pragma once
#include "IGameCharacter.h"
#include "GameObjectCollisionManager.h"

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
		/// <param name="character"> : キャラクター</param>
		void PushBack(IGameCharacter* character);

	private:

		// オブジェクトリスト
		std::list<std::unique_ptr<IGameCharacter>> characters_;

		// オブジェクト同士の判定マネージャー
		GameObjectCollisionManager collMan_;

	};
}
