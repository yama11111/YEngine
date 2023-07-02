#pragma once
#include "IAttack.h"

namespace YGame
{
	class SnortAttack final :
		public IAttack
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="aliveTimer"> : 生存時間</param>
		/// <param name="attackPower"> : 攻撃力</param>
		void Initialize(const Transform::Status& status, const uint32_t aliveTimer, const uint32_t attackPower);

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="info"> : 衝突時情報</param>
		void OnCollision(const CollisionInfo& info) override;

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		CollisionInfo GetCollisionInfo() override;

	public:

		SnortAttack() = default;

		~SnortAttack() = default;

	private:

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		void DrawDebugTextContent() override;

	private:

		// 生存タイマー
		YMath::Timer aliveTimer_;

	};
}