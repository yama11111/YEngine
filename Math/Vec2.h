#pragma once

namespace Math
{
    struct Vec2
    {
    public:
        float x_;
        float y_;
    public:
        // �R���X�g���N�^(��x�N�g��)
        Vec2();
        // �R���X�g���N�^(�����L)
        Vec2(float x, float y);
    public:
        // �m����(����)
        float Length() const;
        // ���� 2��
        constexpr float LengthSquare() const;
        // ���K��
        Vec2 Normalized() const;
        // ��x�N�g����
        constexpr bool IsZero() const;
        // ����
        constexpr float Dot(const Vec2& v) const;
        // ����
        float Distance(const Vec2& v) const;
    public:
        // �P�����Z�q
        Vec2 operator+() const;
        Vec2 operator-() const;
        // ������Z�q
        Vec2& operator+=(const Vec2& v);
        Vec2& operator-=(const Vec2& v);
        Vec2& operator*=(float s);
        Vec2& operator/=(float s);
        // ��r���Z�q
        bool operator==(const Vec2& v);
        bool operator!=(const Vec2& v);
    };
    // �񍀉��Z�q
    inline Vec2 operator+(const Vec2& v1, const Vec2& v2)
    {
        return{ v1.x_ + v2.x_, v1.y_ + v2.y_ };
    }
    inline Vec2 operator-(const Vec2& v1, const Vec2& v2)
    {
        return{ v1.x_ - v2.x_, v1.y_ - v2.y_ };
    }
    inline Vec2 operator*(const Vec2& v, float s)
    {
        return{ v.x_ * s, v.y_ * s };
    }
    inline Vec2 operator*(float s, const Vec2& v)
    {
        return { s * v.x_, s * v.y_ };
    }
    inline Vec2 operator/(const Vec2& v, float s)
    {
        return{ v.x_ / s, v.y_ / s };
    }
}