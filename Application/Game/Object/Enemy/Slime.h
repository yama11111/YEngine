/**
 * @file Slime.h
 * @brief スライムクラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "IEnemy.h"

namespace YGame
{
	class Slime final :
		public IEnemy
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="keys"> : キー</param>
		/// <returns>動的インスタンス</returns>
		static std::unique_ptr<Slime>Create(const Transform::Status& status, const std::string& key);
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="keys"> : キー</param>
		void Initialize(const Transform::Status& status, const std::string& key);

		/// <summary>
		/// 衝突前更新
		/// </summary>
		void UpdateBeforeCollision() override;

		/// <summary>
		/// 衝突後更新
		/// </summary>
		void UpdateAfterCollision() override;

	public:

		Slime() = default;

		~Slime() = default;

	private:

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		ICollisionInfomation GetCollisionInfomation() override;

		/// <summary>
		/// 被弾
		/// </summary>
		/// <param name="damage"> : ダメージ</param>
		/// <param name="isStepOn"> : 踏まれたか</param>
		void Hit(const uint32_t damage, const bool isStepOn) override;

	};
}
