#pragma once
#include "BaseScene.h"

#include "Smoke.h"
#include "Floor.h"

namespace YScene
{
	class TaskScene : public BaseScene
	{
		int a = 0;

		YGame::Smoke smoke_;

		YGame::Floor floor_;

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
		TaskScene() = default;

		// デストラクタ
		~TaskScene() = default;

	};
}
