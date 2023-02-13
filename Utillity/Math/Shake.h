#pragma once
#include "Vector3.h"

namespace YMath
{
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
		void Initialize();
		void Update();
		void Activate(const int swing, const int dekey);
		Vector3 Value() { return value_; }
		bool IsAct() { return isAct_; }
	};
}