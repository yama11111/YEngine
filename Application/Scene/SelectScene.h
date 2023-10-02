#pragma once
#include "BaseScene.h"
#include "SelectDrawer.h"
#include "Camera.h"

namespace YGame
{
	// セレクトシーン
	class SelectScene : public BaseScene
	{

	private:

		SelectDrawer selectDra_;

		uint32_t stageIndex_ = 0;

		// ビュープロジェクション
		ViewProjection transferVP_;
		Camera camera_;

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

