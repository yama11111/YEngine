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

		// �x�N�g��
		Vector3 vector_;

		// �����x
		Vector3 accel_;

		// �ő�l
		Vector3 max_;

	};
}
