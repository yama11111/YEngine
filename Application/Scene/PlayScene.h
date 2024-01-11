#pragma once
#include "BaseScene.h"
#include "GameObjectManager.h"
#include "PauseManager.h"
#include "GameCamera.h"
#include "ScoreManager.h"
#include "UIDrawer.h"
#include "BeginingDrawer.h"

#include "Level.h"

#include "DrawObjectForPostEffect.h"

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

		// オブジェクトマネージャー
		GameObjectManager* pObjectMan_ = nullptr;

		// カメラ
		GameCamera camera_;

		// 転送用ビュープロジェクション
		ViewProjection transferVP_;

		// スコアマネージャー
		ScoreManager* pScoreManager_ = nullptr;

		// UIマネージャー
		UIDrawer uiDra_;

		// 開始演出描画クラス
		BeginingDrawer beginingDra_;
		
		// 開始フラグ
		bool isStart_ = false;
		
		// 停止フラグ
		bool isStop_ = false;

		PauseManager pause_; 

		PostEffect* pPostEffect_;
		std::unique_ptr<DrawObjectForPostEffect> objPE_;

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
