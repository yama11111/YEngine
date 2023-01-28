//#pragma once
//#include "Shake.h"
//#include "Vec4.h"
//
//namespace YActor
//{
//	class ChargeActor
//	{
//	private:
//		// 動いているかフラグ
//		bool isAct_ = false;
//		// 動いていたかフラグ
//		bool isElderAct_ = false;
//		// 揺れ
//		YMath::Shake shake_;
//		// 揺れ幅
//		int shakeVal_ = 0;
//		// 色
//		YMath::Vec4 color_;
//		// チカチカフラグ
//		bool isFliclering_ = false;
//	public:
//		// 初期化
//		void InitializeChargeAction();
//		// 動かす
//		void ActivateChargeAction();
//		// 更新
//		void UpdateChargeAction();
//	public:
//		// 実値取得 (揺れ)
//		YMath::Vec3 ChargeActionShakeValue();
//		// 実値取得 (色)
//		YMath::Vec4 ChargeActionColor();
//		// 動いているか
//		bool IsActChargeAction() { return isElderAct_; }
//	};
//}