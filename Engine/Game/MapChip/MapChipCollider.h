#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace YGame
{
	class MapChipCollider
	{

	protected:

		/// <summary>
		/// マップ衝突設定初期化
		/// </summary>
		/// <param name="scale"> : 大きさ</param>
		void Initialize(const  YMath::Vector3& scale);
	
	public:
		
		// 位置取得 (参照)
		virtual YMath::Vector3& PosRef() = 0;
		
		// 大きさ取得
		YMath::Vector3 Scale() const { return scale_; }
		
		// スピード取得 (参照)
		virtual YMath::Vector3& SpeedRef() = 0;
		
		// 地上にいるか
		bool IsLanding() const { return isLanding_; }
		
		// 地上にいたか
		bool IsElderLanding() const { return isElderLanding_; }
		
	public:

		// 地上にいるか設定
		void SetIsLanding(const bool isLanding) { isLanding_ = isLanding; }
		
		// 地上にいたか設定
		void SetIsElderLanding(const bool isElderLanding) { isElderLanding_ = isElderLanding; }
	
	private:
		
		// 大きさ
		YMath::Vector3 scale_;
		
		// 地上にいるか 
		bool isLanding_ = false;
		
		// 地上にいたか 
		bool isElderLanding_ = false;
	
	};
}
