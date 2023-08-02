#pragma once

namespace YMath
{
    struct Vector2
    {
    public:
        float x_;
        float y_;
    public:
        // �R���X�g���N�^(��x�N�g��)
        Vector2();
        // �R���X�g���N�^(�����L)
        Vector2(float x, float y);
    public:
        // �m����(����)
        float Length() const;
        // ���� 2��
        constexpr float LengthSquare() const;
        // ���K��
        Vector2 Normalized() const;
        // ��x�N�g����
        constexpr bool IsZero() const;
        // ����
        constexpr float Dot(const Vector2& v) const;
        // ����
        float Distance(const Vector2& v) const;
    public:
        // �P�����Z�q
        Vector2 operator+() const;
        Vector2 operator-() const;
        // ������Z�q
        Vector2& operator+=(const Vector2& v);
        Vector2& operator-=(const Vector2& v);
        Vector2& operator*=(float s);
        Vector2& operator/=(float s);
        // ��r���Z�q
        bool operator==(const Vector2& v);
        bool operator!=(const Vector2& v);
    };
    // �񍀉��Z�q
    inline Vector2 operator+(const Vector2& v1, const Vector2& v2)
    {
        return{ v1.x_ + v2.x_, v1.y_ + v2.y_ };
    }
    inline Vector2 operator-(const Vector2& v1, const Vector2& v2)
    {
        return{ v1.x_ - v2.x_, v1.y_ - v2.y_ };
    }
    inline Vector2 operator*(const Vector2& v, float s)
    {
        return{ v.x_ * s, v.y_ * s };
    }
    inline Vector2 operator*(float s, const Vector2& v)
    {
        return { s * v.x_, s * v.y_ };
    }
    inline Vector2 operator/(const Vector2& v, float s)
    {
        return{ v.x_ / s, v.y_ / s };
    }

    using Vec2 = Vector2;
}