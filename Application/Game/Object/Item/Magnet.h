#pragma once
#include "IItem.h"

namespace YGame
{
	class Magnet :
		public IItem
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>		
		/// <param name="drawKeys"> : 描画キー</param>
		/// <returns>動的インスタンス</returns>
		static std::unique_ptr<Magnet>Create(
			const Transform::Status& status,
			const std::vector<std::string>& drawKeys);

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

		Magnet() = default;

		~Magnet() = default;

	private:

		// 動作フラグ
		bool isAct_ = false;

		// 動作タイマー
		YMath::Timer actTimer_;

		// プレイヤートランスフォームポインタ
		Transform* pPlayerTrfm_ = nullptr;

	private:

		/// <summary>
		/// 位置更新
		/// </summary>
		void UpdatePos() override;

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
	};
}
