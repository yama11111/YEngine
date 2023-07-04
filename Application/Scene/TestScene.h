#pragma once
#include "BaseScene.h"
#include "BaseDrawer.h"

namespace YScene
{
	// テストシーン
	class TestScene : public BaseScene
	{

	private:

		YGame::Transform transform_;

		std::list<std::unique_ptr<YGame::BaseDrawer>> drawers_;

		YGame::ViewProjection vp_;

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
		TestScene() = default;
		
		// デストラクタ
		~TestScene() = default;

	};
}
