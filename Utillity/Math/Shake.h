#pragma once
#include "Vector3.h"

namespace YMath
{
	class Shake
	{
	private:
		// —h‚ê‚Ä‚¢‚é—Ê
		Vector3 value_{};
		// —h‚ê‚Ä‚¢‚é‚©
		bool isAct_ = false;
		// —h‚ê‚é—Ê (—”)
		int swing_ = 0;
		// Œ¸Š—Ê
		int dekey_ = 0;
	public:
		void Initialize();
		void Update();
		void Activate(const int swing, const int dekey);
		Vector3 Value() { return value_; }
		bool IsAct() { return isAct_; }
	};
}