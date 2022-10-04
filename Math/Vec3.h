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
		Vec3(); // ��x�N�g��
		Vec3(float x, float y, float z);

		float Length() const;					// �m����(����)
		constexpr float LengthSquare() const;	// ���� 2��
		Vec3 Normalized() const;				// ���K��
		constexpr bool IsZero() const;			// ��x�N�g����

		constexpr float Dot(const Vec3& v) const; // ����
		Vec3 Cross(const Vec3& v); // �O��
		float Distance(const Vec3& v) const; // ����
	public:
		// �P�����Z�q
		Vec3 operator+() const;
		Vec3 operator-() const;

		// ������Z�q
		Vec3& operator+=(const Vec3& v);
		Vec3& operator-=(const Vec3& v);
		Vec3& operator*=(float s);
		Vec3& operator/=(float s);
	};

	// �񍀉��Z�q
	inline Vec3 operator+(const Vec3& v1, const Vec3& v2);
	inline Vec3 operator-(const Vec3& v1, const Vec3& v2);
	inline Vec3 operator*(const Vec3& v, float s);
	inline Vec3 operator*(float s, const Vec3& v);
	inline Vec3 operator/(const Vec3& v, float s);
}