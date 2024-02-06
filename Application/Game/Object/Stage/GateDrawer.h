#pragma once
#include "BaseDrawer.h"
#include "Ease.h"
#include "Timer.h"

namespace YGame
{
	class GateDrawer final :
		public BaseDrawer
	{

	public:

		// アニメーション
		enum class AnimationType : uint32_t
		{
			// 立ち
			eIdle = 0b1,

			// 通過
			ePass = 0b1 << 1,
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="pParentWorldPos"> : 親ワールド座標ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<GateDrawer> Create(
			Transform* pParent,
			YMath::Vector3* pParentWorldPos,
			const size_t drawPriority);

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="pParentWorldPos"> : 親ワールド座標ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Initialize(
			Transform* pParent,
			YMath::Vector3* pParentWorldPos,
			const size_t drawPriority) override;

	public:

		GateDrawer() = default;

		~GateDrawer() = default;

	private:

		std::unique_ptr<ConstBufferObject<CBColor>> cbInsideColor_;

		YMath::Ease<float> passRotaEas_;
		YMath::Ease<float> passScaleEas_;

	private:

		/// <summary>
		/// オブジェクト初期化
		/// </summary>
		void InitializeObjects() override;

		/// <summary>
		/// タイマー初期化
		/// </summary>
		void InitializeTimers() override;

		/// <summary>
		/// アニメーション準備
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="frame"> : 再生フレーム</param>
		void GetReadyForAnimation(const uint32_t index) override;

		/// <summary>
		/// アニメーション更新
		/// </summary>
		void UpdateAnimation() override;
	};
}
