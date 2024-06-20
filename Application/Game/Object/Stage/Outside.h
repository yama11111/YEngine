/**
 * @file Outside.h
 * @brief 外側クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "BaseStageObject.h"

namespace YGame
{
	class Outside final :
		public BaseStageObject
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="key"> : キー</param>
		/// <returns>動的インスタンス</returns>
		static std::unique_ptr<Outside> Create(const Transform::Status& status, const WorldKey key);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="key"> : キー</param>
		void Initialize(const Transform::Status& status, const WorldKey key);

	public:

		/// <summary>
		/// 衝突前更新
		/// </summary>
		void UpdateBeforeCollision() override;

		/// <summary>
		/// 衝突後更新
		/// </summary>
		void UpdateAfterCollision() override;

	public:

		Outside() = default;

		~Outside() = default;

	private:

	};
}

