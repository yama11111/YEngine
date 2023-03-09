#pragma once
#include "Shake.h"
#include "Vector4.h"

namespace YGame
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
		void Initialize();
		// 動かす
		void Activate(const float shakeValue, const unsigned int frame);
		// 更新
		void Update();
	public:
		// 実値取得 (揺れ)
		YMath::Vector3 ShakeValue();
		// 実値取得 (色)
		YMath::Vector4 ColorValue();
		// 動いているか
		bool IsActHitAction() { return isAct_; }
	};
}
