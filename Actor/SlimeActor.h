#pragma once
#include "Lerp.h"
#include "Timer.h"
#include <vector>

namespace YActor
{
	class SlimeActor
	{
	private:
		// 動き
		enum class  Action
		{
			None,		 // 無し
			Elasticity,	 // 伸び縮み
			Normal,		 // 通常
		};
	private:
		// 動いているかフラグ
		bool isAct_ = false;
		// 現在の動き
		Action action_ = Action::None;
		// イージング
		YMath::Ease<YMath::Vec3> ease_;
		// 終了値
		std::vector<YMath::Vec3> ends_;
		// 現在のインデックス
		size_t currentIdx_ = 0;
		// タイマー
		YMath::Timer timer_;
		// 実値
		YMath::Vec3 value_;
	public:
		// 初期化
		void InitializeSlimeAct();
		// 動かす
		void ActivateSlimeAct(const std::vector<YMath::Vec3> ends, const unsigned int frame);
		// 更新
		void UpdateSlimeAct();
		// 実値取得
		YMath::Vec3 SlimeActValue();
	private:
		// 動き切り替え
		void ChangeAction();
		// 実値更新
		void UpdateValue();
	};
}

