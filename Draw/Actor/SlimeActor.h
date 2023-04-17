#pragma once
#include "Lerp.h"
#include "Timer.h"
#include <vector>

namespace YGame
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
		// 揺れステータス
		struct JiggleState
		{
			YMath::Vector3 value_;
			unsigned int frame_;
			float exponent_ = 2.0f;
		};
	private:
		// 動いているかフラグ
		bool isAct_ = false;
		// 現在の動き
		Action action_ = Action::None;
		// イージング
		YMath::Ease<YMath::Vector3> ease_;
		// 終了値
		std::vector<JiggleState> jiggles_;
		// 現在のインデックス
		size_t currentIdx_ = 0;
		// タイマー
		YMath::Timer timer_;
		// 実値
		YMath::Vector3 value_;
	public:
		// 初期化
		void Initialize();
		/// <summary>
		/// 動かす
		/// </summary>
		/// <param name="jiggles"> : 揺れステータス</param>
		/// <param name="---------------------------"></param>
		/// <param name="(Vector3) jiggles.value_"> : 揺れる量</param>
		/// <param name="(uint) jiggles.frame_"> : フレーム</param>
		/// <param name="(float) jiggles.exponent_"> : 指数</param>
		void Activate(const std::vector<JiggleState>& jiggles);
		// 更新
		void Update();
	public:
		// 実値取得
		YMath::Vector3 JiggleValue();
	private:
		// 動き切り替え
		void ChangeAction();
		// 実値更新
		void UpdateValue();
	public:
		virtual ~SlimeActor() = default;
	};
}

