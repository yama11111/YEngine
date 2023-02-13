#pragma once
#include "Vector3.h"

namespace YMath
{
	class Shake
	{
	private:
		// �h��Ă����
		Vector3 value_{};
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
		Vector3 Value() { return value_; }
		bool IsAct() { return isAct_; }
	};
}