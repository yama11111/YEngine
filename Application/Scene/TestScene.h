#pragma once
#include "BaseScene.h"
#include "DrawObjectForSprite2D.h"

namespace YGame
{
	class TestScene :
		public BaseScene
	{

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

	private:

		std::unique_ptr<DrawObjectForSprite2D> circle_;
		
		std::unique_ptr<DrawObjectForSprite2D> box_;
		
		std::unique_ptr<DrawObjectForSprite2D> triangle_;

	};
}
