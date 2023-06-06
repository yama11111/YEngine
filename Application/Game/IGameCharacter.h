#pragma once
#include "IGameObject.h"
#include "CharacterStatus.h"
#include "Speed.h"

namespace YGame
{
	class IGameCharacter :
		public IGameObject
	{

	public:

		IGameCharacter() = default;

		virtual ~IGameCharacter() = default;

	protected:

		/// <summary>
		/// ジャンプ
		/// </summary>
		void Jump();

		/// <summary>
		/// 重力
		/// </summary>
		void UpdatePhysics();

	protected:

		// スピード
		YMath::Speed speed_;

		// ジャンプカウンター
		unsigned int jumpCounter_ = 0;
		
		// 最大ジャンプ回数
		unsigned int maxJumpCount_ = 0;

		// 着地フラグ
		bool isLanding_ = false;

		// キャラクターステータス
		CharacterStatus status_;
	};
}
