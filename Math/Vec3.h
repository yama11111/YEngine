#pragma once

namespace Math
{
	struct Vec3
	{
	public:
		float x_;
		float y_;
		float z_;
	public:
		// �R���X�g���N�^(��x�N�g��)
		Vec3();
		// �R���X�g���N�^(�����L)
		Vec3(float x, float y, float z);
	public:
		// �m����(����)
		float Length() const;
		// ���� 2��
		constexpr float LengthSquare() const;
		// ���K��
		Vec3 Normalized() const;
		// ��x�N�g����
		constexpr bool IsZero() const;
		// ����
		constexpr float Dot(const Vec3& v) const;
		// �O��
		Vec3 Cross(const Vec3& v);
		// ����
		float Distance(const Vec3& v) const;
	public:
		// �P�����Z�q
		Vec3 operator+() const;
		Vec3 operator-() const;
		// ������Z�q
		Vec3& operator+=(const Vec3& v);
		Vec3& operator-=(const Vec3& v);
		Vec3& operator*=(float s);
		Vec3& operator/=(float s);
		// ��r���Z�q
		bool operator==(const Vec3& v);
		bool operator!=(const Vec3& v);
	};
	// �񍀉��Z�q
	inline Vec3 operator+(const Vec3& v1, const Vec3& v2)
	{
		return { v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_ };
	}
	inline Vec3 operator-(const Vec3& v1, const Vec3& v2)
	{
		return { v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_ };
	}
	inline Vec3 operator*(const Vec3& v, float s)
	{
		return { v.x_ * s, v.y_ * s, v.z_ * s };
	}
	inline Vec3 operator*(float s, const Vec3& v)
	{
		return { s * v.x_, s * v.y_, s * v.z_ };
	}
	inline Vec3 operator/(const Vec3& v, float s)
	{
		return { v.x_ / s, v.y_ / s, v.z_ / s };
	}
}