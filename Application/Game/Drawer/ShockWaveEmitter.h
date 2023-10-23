#pragma once
#include "DrawObjectForSprite3D.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "Ease.h"
#include "Timer.h"
#include <array>
#include <memory>

namespace YGame
{
	class ShockWaveEmitter final
	{

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void Initialize(ViewProjection* pVP);

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pos"> : 位置</param>
		static void Emit(const YMath::Vector3& pos);

		/// <summary>
		/// 更新
		/// </summary>
		static void Update();

		/// <summary>
		/// 描画
		/// </summary>
		static void Draw();

	private:

		class ShockWave final
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
			void Pop(const YMath::Vector3& pos);

			/// <summary>
			/// 動作中か
			/// </summary>
			/// <returns>動作フラグ</returns>
			inline bool IsAct() const { return isAct_; }

		private:

			// オブジェクト
			std::unique_ptr<DrawObjectForSprite3D> obj_;

			// 色
			std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;


			// 動作フラグ
			bool isAct_ = false;

			// アニメーションタイマー
			YMath::Timer actTim_;

			// スケールイージング
			YMath::Ease<float> scaEas_;

			// アルファ値イージング
			YMath::Ease<float> alphaEas_;
		};

	private:

		// 衝撃波配列
		static std::array<ShockWave, 10> shockWave_;

		// ビュープロジェクションポインタ
		static ViewProjection* spVP_;

	};
}
