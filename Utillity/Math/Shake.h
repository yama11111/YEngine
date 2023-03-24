#pragma once
#include "Vector3.h"

namespace YMath
{
	// 揺れ
	class Shake
	{
	private:
		// 揺れている量
		Vector3 value_{};
		// 揺れているか
		bool isAct_ = false;
		// 揺れる量 (乱数)
		int swing_ = 0;
		// 減衰量
		int dekey_ = 0;
	public:
		// 初期化
		void Initialize();
		// 更新
		void Update();
		/// <summary>
		/// 動作開始
		/// </summary>
		/// <param name="swing"> : 揺れる量</param>
		/// <param name="dekey"> : 減衰量</param>
		void Activate(const int swing, const int dekey);
	public:
		// 揺れ量
		Vector3 Value() const { return value_; }
		// 動作中か
		bool IsAct() const { return isAct_; }
	};
}