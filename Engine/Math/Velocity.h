#pragma once
#include"Vector3.h"

namespace YMath
{
	class Velocity
	{

	public:

	
	public:

		Velocity();
		
		virtual ~Velocity();

	private:

		// ベクトル
		Vector3 vector_;

		// 加速度
		Vector3 accel_;

		// 最大値
		Vector3 max_;

	};
}
