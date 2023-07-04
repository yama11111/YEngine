#pragma once
#include "IPet.h"

namespace YGame
{
	class Horse final:
		public IPet
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		void Initialize(const Transform::Status& status);

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

		/// <summary>
		/// ジャンプ
		/// </summary>
		/// <param name="isJumpCount"> : カウントするか</param>
		void Jump(const bool isJumpCount = true) override;

		/// <summary>
		/// 攻撃
		/// </summary>
		void Attack() override;

	public:

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		CollisionInfo GetCollisionInfo() override;

		/// <summary>
		/// 乗る位置の高さ取得
		/// </summary>
		/// <returns>乗る位置の高さ</returns>
		float RidingPosHeight() override;

	public:

		Horse() = default;

		~Horse() = default;

	protected:

		/// <summary>
		/// 衝突時処理
		/// </summary>
		void Hit() override;
	};
}
