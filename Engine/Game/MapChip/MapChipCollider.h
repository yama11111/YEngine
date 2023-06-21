#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <cstdint>

namespace YGame
{
	class MapChipCollider
	{
	
	public:

		/// <summary>
		/// 位置取得 (参照)
		/// </summary>
		/// <returns>位置(参照)</returns>
		virtual YMath::Vector3& PosRef() = 0;
		
		/// <summary>
		/// 大きさ取得
		/// </summary>
		/// <returns>大きさ</returns>
		inline YMath::Vector3 Scale() const { return scale_; }
		
		/// <summary>
		/// スピード取得 (参照)
		/// </summary>
		/// <returns>スピード(参照)</returns>
		virtual YMath::Vector3& SpeedRef() = 0;

		/// <summary>
		/// アタリ判定ビット取得
		/// </summary>
		/// <returns>アタリ判定ビット</returns>
		inline uint8_t CollisionBit() const { return collisionBit_; }
		
	public:

		/// <summary>
		/// アタリ判定ビット設定
		/// </summary>
		/// <param name="collisionBit"> : アタリ判定ビット</param>
		inline void SetCollisionBit(const uint8_t collisionBit) { collisionBit_ = collisionBit; }
	
	public:

		MapChipCollider() = default;

		virtual ~MapChipCollider() = default;

	protected:

		/// <summary>
		/// マップ衝突設定初期化
		/// </summary>
		/// <param name="scale"> : 大きさ</param>
		void Initialize(const  YMath::Vector3& scale);
	
	private:
		
		// 大きさ
		YMath::Vector3 scale_;

		// 跳ね返るか
		bool isBounce_ = false;

		// アタリ判定ビット
		uint8_t collisionBit_;
	};
}
