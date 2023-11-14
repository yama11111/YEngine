#pragma once
#include "IEnemy.h"

namespace YGame
{
	class Slime final :
		public IEnemy
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		void Initialize(const Transform::Status& status);

		/// <summary>
		/// 衝突前更新
		/// </summary>
		void UpdateBeforeCollision() override;

		/// <summary>
		/// 衝突後更新
		/// </summary>
		void UpdateAfterCollision() override;

	public:

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		CollisionInfo GetCollisionInfo() override;

	public:

		Slime() = default;

		~Slime() = default;

	private:

		/// <summary>
		/// 被弾
		/// </summary>
		/// <param name="damage"> : ダメージ</param>
		/// <param name="isStepOn"> : 踏まれたか</param>
		void Hit(const uint32_t damage, const bool isStepOn) override;

	};
}
