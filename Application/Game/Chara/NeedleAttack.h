#pragma once
#include "IAttack.h"

namespace YGame
{
	class NeedleAttack final :
		public IAttack
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="aliveTimer"> : 生存時間</param>
		/// <param name="emitPos"> : 発生位置</param>
		/// <param name="acceleration"> : 加速度</param>
		/// <param name="maxspeed"> : 最高速度</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="attackPower"> : 攻撃力</param>
		/// <returns>動的インスタンス</returns>
		static std::unique_ptr<NeedleAttack>Create(
			const uint32_t aliveTimer,
			const YMath::Vector3& emitPos,
			const YMath::Vector3& acceleration,
			const YMath::Vector3& maxSpeed,
			const float radius,
			const uint32_t attackPower);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="aliveTimer"> : 生存時間</param>
		/// <param name="emitPos"> : 発生位置</param>
		/// <param name="acceleration"> : 加速度</param>
		/// <param name="maxspeed"> : 最高速度</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="attackPower"> : 攻撃力</param>
		void Initialize(
			const uint32_t aliveTimer,
			const YMath::Vector3& emitPos,
			const YMath::Vector3& acceleration,
			const YMath::Vector3& maxSpeed,
			const float radius,
			const uint32_t attackPower);

		/// <summary>
		/// 衝突前更新
		/// </summary>
		void UpdateBeforeCollision() override;

		/// <summary>
		/// 衝突後更新
		/// </summary>
		void UpdateAfterCollision() override;

	public:

		NeedleAttack() = default;

		~NeedleAttack() = default;

	private:

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		InfoOnCollision GetInfoOnCollision() override;

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="info"> : 衝突時情報</param>
		void OnCollision(const InfoOnCollision& info) override;

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		void DrawDebugTextContent() override;

	private:

		// 生存タイマー
		YMath::Timer aliveTimer_;
	};
}