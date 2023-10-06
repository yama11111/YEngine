#pragma once
#include "UINumber.h"
#include "CBColor.h"
#include "ConstBufferObject.h"
#include "Ease.h"
#include "Timer.h"
#include <array>
#include <memory>

namespace YGame
{
	class DamageEmitter final
	{

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void Initialize(ViewProjection* pVP);

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="damageVal"></param>
		static void Emit(const YMath::Vector3& pos, const uint32_t damageVal);

		/// <summary>
		/// 更新
		/// </summary>
		static void Update();

		/// <summary>
		/// 描画
		/// </summary>
		static void Draw();

	private:

		class Damage final
		{

		public:

			/// <summary>
			/// 初期化
			/// </summary>
			void Initialize(ViewProjection* pVP);

			/// <summary>
			/// リセット (中身だけ初期化)
			/// </summary>
			void Reset();

			/// <summary>
			/// 更新
			/// </summary>
			void Update();

			/// <summary>
			/// 描画
			/// </summary>
			void Draw();

		public:

			/// <summary>
			/// ダメージ生成
			/// </summary>
			/// <param name="pos"> : 位置</param>
			/// <param name="damageValue"> : ダメージ量</param>
			void Pop(const YMath::Vector3& pos, const uint32_t damageValue);

			/// <summary>
			/// 動作中か
			/// </summary>
			/// <returns>動作フラグ</returns>
			inline bool IsAct() const { return isAct_; }

		private:

			// トランスフォーム
			Transform trfm_;

			// X軸ビルボードフラグ
			bool isXBillboard_ = false;

			// Y軸ビルボードフラグ
			bool isYBillboard_ = false;

			// 数字
			std::unique_ptr<UINumber> uiNum_;

			// 色
			std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;


			// 動作フラグ
			bool isAct_ = false;

			// 生成タイマー
			YMath::Timer popTim_;

			// 上昇イージング
			YMath::Ease<float> upEas_;

			// スケールイージング
			YMath::Ease<float> popScaEas_;

			// 残存タイマー
			YMath::Timer remainTim_;

			// 消失タイマー
			YMath::Timer vanishTim_;

			// アルファ値イージング
			YMath::Ease<float> vanishAlphaEas_;
		};

	private:

		// ダメージ配列
		static std::array<Damage, 10> damage_;

		// ビュープロジェクションポインタ
		static ViewProjection* spVP_;

	};
}
