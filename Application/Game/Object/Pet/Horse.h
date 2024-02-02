#pragma once
#include "IPet.h"

namespace YGame
{
	class Horse final:
		public IPet
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <returns>動的インスタンス</returns>
		static std::unique_ptr<Horse>Create(const Transform::Status& status);

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
		/// ジャンプ
		/// </summary>
		/// <param name="isJumpCount"> : カウントするか</param>
		void Jump(const bool isJumpCount = true) override;

		/// <summary>
		/// 攻撃
		/// </summary>
		void Attack() override;

		/// <summary>
		/// 乗られる
		/// </summary>
		void Rideen() override;
		
		/// <summary>
		/// 降りられる
		/// </summary>
		void GotOff() override;

	public:

		/// <summary>
		/// 乗る位置の高さ取得
		/// </summary>
		/// <returns>乗る位置の高さ</returns>
		YMath::Vector3 RidingPosHeight() override;

	public:

		Horse() = default;

		~Horse() = default;

	private:

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		InfoOnCollision GetInfoOnCollision() override;

		/// <summary>
		/// 衝突時処理
		/// </summary>
		void Hit() override;
	};
}