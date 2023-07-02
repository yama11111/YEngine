#pragma once
#include "BaseScene.h"
#include "MapChipManager.h"
#include "CharacterManager.h"
#include "ScrollCamera.h"

#include "Level.h"

namespace YScene
{
	// ゲームシーン
	class PlayScene : public BaseScene
	{

	public:

#pragma region リソース


#pragma endregion

#pragma region ゲームオブジェクト

		// レベル
		YGame::Level* pLevel_;

		// キャラクターマネージャー
		YGame::CharacterManager* pCharacterMan_ = nullptr;

		// マップチップマネージャー
		YGame::MapChipManager* pMapChipManager_ = nullptr;

		// スクロールカメラ
		YGame::ScrollCamera scrollCamera_;

		// 転送用ビュープロジェクション
		YGame::ViewProjection transferVP_;

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
