#pragma once

namespace Math
{
	struct Vec3
	{
	public:
		float x;
		float y;
		float z;
	public:
		constexpr Vec3(); // ��x�N�g��
		constexpr Vec3(const float x, const float y, const float z);

		float Length() const;					// �m����(����)
		constexpr float LengthSquare() const;	// ���� 2��
		Vec3 Normalized() const;				// ���K��
		constexpr bool IsZero() const;			// ��x�N�g����

		constexpr float Dot(const Vec3& v) const; // ����
		Vec3 Cross(const Vec3& v); // �O��
		float Distance(const Vec3& v) const; // ����
	public:
		// �P�����Z�q
		constexpr Vec3 operator+() const;
		constexpr Vec3 operator-() const;
		constexpr Vec3 operator+(const Vec3& v) const;
		constexpr Vec3 operator-(const Vec3& v) const;
		constexpr Vec3 operator*(float s) const;
		constexpr Vec3 operator/(float s) const;

		// ������Z�q
		Vec3& operator+=(const Vec3& v);
		Vec3& operator-=(const Vec3& v);
		Vec3& operator*=(float s);
		Vec3& operator/=(float s);
	};

	// �񍀉��Z�q
	inline constexpr Vec3 operator *(float s, const Vec3& v);
}