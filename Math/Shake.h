#pragma once
#include "Vec3.h"
#include "Random.h"

namespace Math
{
	class Shake {
	private:
		Vec3 value{};			// À”’l
		bool isShake = false;	// —h‚ê‚Ä‚¢‚é‚©
		float swingValue = 0;	// —h‚ê‚é—Ê (—”)
		float dekey = 0;		// Œ¸Š—Ê
		Random* rand = nullptr;
	public:
		void Initialize();
		void Update();
		void Shaking(const float swing, const float dekey);
		Vec3 GetValue() { return value; }
		bool IsShake() { return isShake; }
		float Ratio() { return 1.0f - dekey / swingValue; }
	};
}
