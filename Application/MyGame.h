#pragma once
#include "YFramework.h"
#include "PipelineManager.h"

namespace YBase
{
	class MyGame : public YFramework
	{

	private:

		YGame::PipelineManager* pipelineMan_ = nullptr;

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <returns>成功したか</returns>
		bool Initialize() override;
		
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

	private:

		/// <summary>
		/// パイプライン初期化
		/// </summary>
		void InitializePipelines();

		/// <summary>
		/// ゲームシーン描画
		/// </summary>
		void DrawGameScene();

	};
}
