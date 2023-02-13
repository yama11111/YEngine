#pragma once

namespace YMath
{
	struct Vector3
	{
	public:
		float x_;
		float y_;
		float z_;
	public:
		// �R���X�g���N�^(��x�N�g��)
		Vector3();
		// �R���X�g���N�^(�����L)
		Vector3(float x, float y, float z);
	public:
		// �m����(����)
		float Length() const;
		// ���� 2��
		constexpr float LengthSquare() const;
		// ���K��
		Vector3 Normalized() const;
		// ��x�N�g����
		constexpr bool IsZero() const;
		// ����
		constexpr float Dot(const Vector3& v) const;
		// �O��
		Vector3 Cross(const Vector3& v) const;
		// ����
		float Distance(const Vector3& v) const;
	public:
		// �P�����Z�q
		Vector3 operator+() const;
		Vector3 operator-() const;
		// ������Z�q
		Vector3& operator+=(const Vector3& v);
		Vector3& operator-=(const Vector3& v);
		Vector3& operator*=(float s);
		Vector3& operator/=(float s);
		// ��r���Z�q
		bool operator==(const Vector3& v);
		bool operator!=(const Vector3& v);
	};
	// �񍀉��Z�q
	inline Vector3 operator+(const Vector3& v1, const Vector3& v2)
	{
		return { v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_ };
	}
	inline Vector3 operator-(const Vector3& v1, const Vector3& v2)
	{
		return { v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_ };
	}
	inline Vector3 operator*(const Vector3& v, float s)
	{
		return { v.x_ * s, v.y_ * s, v.z_ * s };
	}
	inline Vector3 operator*(float s, const Vector3& v)
	{
		return { s * v.x_, s * v.y_, s * v.z_ };
	}
	inline Vector3 operator/(const Vector3& v, float s)
	{
		return { v.x_ / s, v.y_ / s, v.z_ / s };
	}

	using Vec3 = Vector3;
}