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
		YMath::Ease<YMath::Vector3> ease_;
		// 終了値
		std::vector<YMath::Vector3> ends_;
		// 現在のインデックス
		size_t currentIdx_ = 0;
		// タイマー
		YMath::Timer timer_;
		// 実値
		YMath::Vector3 value_;
	public:
		// 初期化
		void InitializeSlimeAction();
		// 動かす
		void ActivateSlimeAction(const std::vector<YMath::Vector3> ends, const unsigned int frame);
		// 更新
		void UpdateSlimeAction();
	public:
		// 実値取得
		YMath::Vector3 SlimeActionValue();
	private:
		// 動き切り替え
		void ChangeAction();
		// 実値更新
		void UpdateValue();
	};
}

