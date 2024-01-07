/**
 * @file StatusDrawer.h
 * @brief プレイヤーのステータスUIを表示するクラス
 * @author Yamanaka Rui
 * @date 2024/01/05
 */

#pragma once
#include "HPGaugeDrawer.h"
#include "SpeedLevelDrawer.h"

namespace YGame
{
	class StatusDrawer final
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <returns>ステータス描画クラスポインタ (動的インスタンス)</returns>
		static StatusDrawer* Create(YMath::Matrix4* pParent, ViewProjection* pVP);

		/// <summary>
		/// 読み込み
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		void Initialize(YMath::Matrix4* pParent, ViewProjection* pVP);
		
		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="hp"> : HP</param>
		/// <param name="maxHP"> : 最大HP</param>
		/// <param name="speedLevel"> : 速度レベル</param>
		void Update(const uint32_t hp, const uint32_t maxHP, const uint32_t speedLevel);

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	
	private:

		// トランスフォーム
		Transform transform_;

		// ステータスUI
		std::unique_ptr<BaseDrawObject> statusUI_;

		// HPゲージ
		std::unique_ptr<HPGaugeDrawer> hpGauge_;

		// スピードレベル
		std::unique_ptr<SpeedLevelDrawer> speedLev_;
	
	};
}
