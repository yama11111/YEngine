#pragma once
#include "Vec3.h"
#include "Random.h"

namespace Math
{
	class Shake {
	private:
		Vec3 value{};			// �����l
		bool isShake = false;	// �h��Ă��邩
		float swingValue = 0;	// �h���� (����)
		float dekey = 0;		// ������
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
