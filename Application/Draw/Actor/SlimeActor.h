#pragma once
#include "Ease.h"
#include "Timer.h"
#include "Vector3.h"
#include <vector>

namespace YGame
{
	class SlimeActor
	{
	
	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// ブヨブヨアニメーション
		/// </summary>
		/// <param name="wobbleScaleValues"> : 拡縮値ベクター配列</param>
		/// <param name="frame">"> : フレーム</param>
		/// <param name="exponent">"> : 指数</param>
		void Wobble(const std::vector<YMath::Vector3>& wobbleScaleValues, const uint32_t frame, const float exponent);
		
		/// <summary>
		/// 更新
		/// </summary>
		void Update();
	
	public:
	
		/// <summary>
		/// 動作中か
		/// </summary>
		/// <returns>動作フラグ</returns>
		inline bool IsAct() const { return isAct_; }

		/// <summary>
		/// 現在の拡縮値取得
		/// </summary>
		/// <returns>現在の拡縮値</returns>
		inline YMath::Vector3 WobbleScaleValue() const { return value_; }
	
	public:
		
		virtual ~SlimeActor() = default;
	
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
		std::vector<YMath::Vector3> wobbleScaleValues_;

		// 指数
		float exponent_ = 0.0f;
		
		// 現在のインデックス
		size_t currentIdx_ = 0;
		
		// タイマー
		YMath::Timer timer_;
		
		// 実値
		YMath::Vector3 value_;
	
	private:
		
		/// <summary>
		/// 動き切り替え
		/// </summary>
		void ChangeAction();
		
		/// <summary>
		/// 実値更新
		/// </summary>
		void UpdateValue();
	
	};
}

