#pragma once
#include "BaseScene.h"
#include "MapChipManager.h"
#include "CharacterManager.h"
#include "ScrollCamera.h"

#include "Level.h"

namespace YGame
{
	// ゲームシーン
	class PlayScene : public BaseScene
	{

	public:

#pragma region リソース


#pragma endregion

#pragma region ゲームオブジェクト

		// レベル
		Level* pLevel_;

		// キャラクターマネージャー
		CharacterManager* pCharacterMan_ = nullptr;

		// マップチップマネージャー
		MapChipManager* pMapChipManager_ = nullptr;

		// スクロールカメラ
		ScrollCamera scrollCamera_;

		// 転送用ビュープロジェクション
		ViewProjection transferVP_;

#pragma endregion

	public:

		/// <summary>
		/// 読み込み
		/// </summary>
		void Load() override;

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize() override;

		/// <summary>
		/// 終了処理
		/// </summary>
		void Finalize() override;

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	public:

		// コンストラクタ
		PlayScene() = default;

		// デストラクタ
		~PlayScene() = default;

	};
}
