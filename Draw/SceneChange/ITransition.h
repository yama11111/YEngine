#pragma once
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"

namespace YGame
{
	// トランジション基底クラス
	class ITransition
	{
	protected:
		// 動作しているか
		bool isAct_ = false;
		// 切り替わっている途中か
		bool isPreChange_ = false;
		// 切り替わりの瞬間
		bool isChangeMoment_ = false;
		// 終了しているか
		bool isEnd_ = false;
		// ローディング用タイマー
		YMath::Timer loadTim_;
	public:
		// リセット(中身だけ初期化)
		virtual void Reset() = 0;
		// 更新
		virtual void Update() = 0;
		// 描画
		virtual void Draw() = 0;
	public:
		// 動作開始
		virtual void Activate() = 0;
		// 切り替わっている途中か
		bool IsPreChange() const { return isPreChange_; }
		// 切り替わりの瞬間か
		bool IsChangeMoment() const { return isChangeMoment_; }
		// 終了しているか
		bool IsEnd() const { return isEnd_; }
	public:
		ITransition() = default;
		virtual ~ITransition() = default;
	};
}
