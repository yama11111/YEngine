#pragma once
#include "Lerp.h"

namespace YGame
{
	// ゲームルール (シングルトン)
	class WorldRuler
	{
	private:
		// 時間スピード
		float timeSpd_ = 1.0f;
		// 重力
		float gravity_ = 0.3f;
		// 摩擦
		float friction_ = 0.5f;

		// 修正フラグ
		bool isModify_ = false;
		
		// カウント
		unsigned int modifyCount_ = 0;
		// 修正時間
		unsigned int modifyFrame_ = 0;

		// 時間スピード補間クラス
		YMath::Ease<float> timeSpdEas_;
		// 重力補間クラス
		YMath::Ease<float> gravityEas_;
		// 摩擦補間クラス
		YMath::Ease<float> frictionEas_;
	public:
		// 初期化
		void Initailze();
		// リセット
		void Reset();
		// 更新
		void Update();
	public:
		/// <summary>
		/// 修正
		/// </summary>
		/// <param name="time"> : 時間 (かかる時間)</param>
		/// <param name="exponent"> : 指数 (緩急)</param>
		void Modify(const unsigned int time, const float exponent = 2.0f);
		
		// 時間スピード取得
		float GetTimeSpeed() const { return timeSpd_; }
		// 時間スピード設定
		void SetTimeSpeed(const float timeSpd);

		// 重力取得
		float GetGravity() const {return gravity_;}
		// 重力設定
		void SetGravity(const float gravity);

		// 摩擦取得
		float GetFriction() const {return friction_;}
		// 摩擦設定
		void SetFriction(const float friction);
	};

	class WorldRuleAdopter
	{
	protected:
		// 適用するか
		bool isApply_ = true;
	protected:
		// 静的ゲームルールポインタ
		static WorldRuler* spWorldRuler_;
	public:
		// 静的初期化
		static void StaticInitialize(WorldRuler* pWorldRuler);
	};
}

