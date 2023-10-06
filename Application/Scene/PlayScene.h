#pragma once
#include "BaseScene.h"
#include "MapChipManager.h"
#include "CharacterManager.h"
#include "PauseManager.h"
#include "ScrollCamera.h"
#include "UIManager.h"

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
		Level* pLevel_ = nullptr;

		// キャラクターマネージャー
		CharacterManager* pCharacterMan_ = nullptr;

		// マップチップマネージャー
		MapChipManager* pMapChipManager_ = nullptr;

		// スクロールカメラ
		ScrollCamera scrollCamera_;

		// 転送用ビュープロジェクション
		ViewProjection transferVP_;

		// UIマネージャー
		UIManager uiMan_;
		
		// 開始フラグ
		bool isStart_ = false;

		// 開始演出用タイマー
		YMath::Timer startTimer_;

		// 開始演出用カメラオフセット
		YMath::Ease<YMath::Vector3> cameraOffset_;
		
		// 停止フラグ
		bool isStop_ = false;

		PauseManager pause_;

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
