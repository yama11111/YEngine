#pragma once
#include "Vec3.h"

namespace Math
{
	class Shake
	{
	private:
		// —h‚ê‚Ä‚¢‚é—Ê
		Vec3 value_{};
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
		Vec3 Value() { return value_; }
		bool IsShake() { return isAct_; }
	};
}