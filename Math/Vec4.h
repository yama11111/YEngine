#pragma once

namespace Math
{
	struct Vec4
	{
	public:
		float r_;
		float g_;
		float b_;
		float a_;
	public:
		// �R���X�g���N�^(��x�N�g��)
		Vec4();
		// �R���X�g���N�^(�����L)
		Vec4(float r, float g, float b, float a);
	};
}
