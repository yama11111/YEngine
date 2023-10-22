#pragma once
#include "IItem.h"

namespace YGame
{
	class Coin final : 
		public IItem
	{
	
	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="pPet"> : ペットポインタ</param>
		void Initialize(const Transform::Status& status);

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="isUpdate"> : 更新するか</param>
		void Update(const bool isUpdate) override;

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
	
	private:
	
	};
}
