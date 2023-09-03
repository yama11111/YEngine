#pragma once
#include "BaseScene.h"
#include "DrawObjectForSprite2D.h"
#include "UIButton.h"
#include "UILetterBox.h"
#include "UINumber.h"
#include "Level.h"

namespace YGame
{
	// セレクトシーン
	class SelectScene : public BaseScene
	{

	private:

#pragma region リソース

		Sprite2D* pLogoSpr_ = nullptr;
		
		Sprite2D* pStickSpr_ = nullptr;

		Sprite2D* pButtonSpr_ = nullptr;
		

#pragma endregion

#pragma region ゲームオブジェクト


		// レベル
		Level* pLevel_ = nullptr;

		std::unique_ptr<DrawObjectForSprite2D> logoObj_;

		std::unique_ptr<DrawObjectForSprite2D> stickObj_;
		
		std::unique_ptr<DrawObjectForSprite2D> buttonObj_;


		std::unique_ptr<UIButton> startButton_;
		
		// 数
		std::array<Transform, 10> nums_;
		std::array<std::unique_ptr<UINumber>, 10> uiNumbers_;

		uint32_t stageIndex_ = 0;

		// 黒帯
		std::unique_ptr<UILetterBox> letterBox_;

		// ビュープロジェクション
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
		SelectScene() = default;
		
		// デストラクタ
		~SelectScene() = default;

	};
}

