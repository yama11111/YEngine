#pragma once
#include "Shake.h"
#include "Vector4.h"
#include <cstdint>

namespace YGame
{
	class HitActor
	{
	
	public:

		void Initialize(const YMath::Vector4& hitColor = YMath::Vector4(1.0f, 0.0f, 0.0f, 0.75f));

		void Update();

		void Hit(const float swing, const float dekey, const float place);

		inline YMath::Vector4 HitColor() const { return hitColor_; }

		inline bool IsAct() const { return isAct_; }

	public:

		HitActor() = default;
		
		virtual ~HitActor() = default;
	
	private:

		// 動いているかフラグ
		bool isAct_ = false;
		
		// 揺れ
		YMath::Shake shake_;
		
		// ヒット時の色
		YMath::Vector4 hitColor_;
	};
}
