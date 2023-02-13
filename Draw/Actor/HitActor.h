#pragma once
#include "Shake.h"
#include "Vector4.h"

namespace YActor
{
	class HitActor
	{
	private:
		// 動いているかフラグ
		bool isAct_ = false;
		// 揺れ
		YMath::Shake shake_;
		// 色
		YMath::Vector4 color_;
		// チカチカフラグ
		bool isFliclering_ = false;
	public:
		// 初期化
		void InitializeHitAction();
		// 動かす
		void ActivateHitAction(const float shakeValue, const unsigned int frame);
		// 更新
		void UpdateHitAction();
	public:
		// 実値取得 (揺れ)
		YMath::Vector3 HitActionShakeValue();
		// 実値取得 (色)
		YMath::Vector4 HitActionColor();
		// 動いているか
		bool IsActHitAction() { return isAct_; }
	};
}
