#pragma once
#include "IItem.h"

namespace YGame
{
	class Life final:
		public IItem
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="key"> : キー</param>
		/// <returns>動的インスタンス</returns>
		static std::unique_ptr<Life>Create(const Transform::Status& status, const WorldKey key);


	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="key"> : キー</param>
		void Initialize(const Transform::Status& status, const WorldKey key);

		/// <summary>
		/// 衝突前更新
		/// </summary>
		void UpdateBeforeCollision() override;

		/// <summary>
		/// 衝突後更新
		/// </summary>
		void UpdateAfterCollision() override;

	public:

		Life() = default;

		~Life() = default;

	private:

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		ICollisionInfomation GetCollisionInfomation() override;

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="info"> : 衝突時情報</param>
		void OnCollision(const ICollisionInfomation& info) override;
	};
}
