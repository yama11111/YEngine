#pragma once
#include "IAttack.h"

namespace YGame
{
	class SlashAttack final:
		public IAttack
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="aliveTimer"> : 生存時間</param>
		/// <param name="pAttackerPos"> : 攻撃者の位置ポインタ</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="attackPower"> : 攻撃力</param>
		void Initialize(
			const uint32_t aliveTimer, 
			YMath::Vector3* pAttackerPos,
			const YMath::Vector3& offset,
			const float radius,
			const uint32_t attackPower);

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

		SlashAttack() = default;

		~SlashAttack() = default;
	
	private:

		// 親ポインタ
		YMath::Vector3* pAttackerPos_ = nullptr;
		
		// オフセット
		YMath::Vector3 offset_;

		// 生存タイマー
		YMath::Timer aliveTimer_;
	
	private:

		/// <summary>
		/// 位置更新
		/// </summary>
		void UpdatePos();

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		void DrawDebugTextContent() override;

	};
}