#pragma once
#include "BaseCharacter.h"

namespace YGame
{
	class IAttack :
		public BaseCharacter
	{

	public:

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="info"> : 衝突時情報</param>
		virtual void OnCollision(const CollisionInfo& info) override;
	
	public:

		IAttack() = default;

		virtual ~IAttack() = default;

	};
}
