#pragma once
#include "Vec3.h"

namespace Math
{
	class Shake
	{
	private:
		// �h��Ă����
		Vec3 value_{};
		// �h��Ă��邩
		bool isAct_ = false;
		// �h���� (����)
		int swing_ = 0;
		// ������
		int dekey_ = 0;
	public:
		void Initialize();
		void Update();
		void Activate(const int swing, const int dekey);
		Vec3 Value() { return value_; }
		bool IsShake() { return isAct_; }
	};
}