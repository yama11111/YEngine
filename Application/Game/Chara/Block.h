#pragma once
#include "GameObject.h"

namespace YGame
{
	class Block : 
		public GameObject
	{
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="pParent"> : 親ポインタ</param>
		void Initialize(
			const Transform::Status& status,
			GameObject* pParent = nullptr);
	
	public:
		
		/// <summary>
		/// 衝突前更新
		/// </summary>
		virtual void UpdateBeforeCollision();
		
		/// <summary>
		/// 衝突後更新
		/// </summary>
		virtual void UpdateAfterCollision();
	
	public:

		Block() = default;
		
		~Block() = default;

	};
}
