/**
 * @file MyGame.h
 * @brief ゲーム全体の動きを管理するクラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "YFramework.h"

namespace YBase
{
	class MyGame final : 
		public YFramework
	{

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
		/// 更新の中身
		/// </summary>
		void UpdateContent() override;

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
		/// パーティクル初期化
		/// </summary>
		void InitializeParticles();

		/// <summary>
		/// シーン遷移初期化
		/// </summary>
		void InitializeTransition();

		/// <summary>
		/// マップデータ読み込み
		/// </summary>
		void LoadMapData();

	};
}
