#pragma once
#include "IPet.h"

namespace YGame
{
	class Horse :
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
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		inline CollisionInfo GetCollisionInfo() override;

	public:

		Horse() = default;

		~Horse() = default;

	public:

	};
}
