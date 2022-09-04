#pragma once

namespace Math
{
    struct Vec2
    {
    public:
        float x;
        float y;
    public:
        constexpr Vec2(); // ��x�N�g��
        constexpr Vec2(const float x, const float y);

        float Length() const;                   // �m����(����)
        constexpr float LengthSquare() const;   // ���� 2��
        Vec2 Normalized() const;                // ���K��
        constexpr bool IsZero() const;          // ��x�N�g����

        constexpr float Dot(const Vec2& v) const; // ����
        float Distance(const Vec2& v) const; // ����
    public:
        // �P�����Z�q
        constexpr Vec2 operator+() const;
        constexpr Vec2 operator-() const;
        constexpr Vec2 operator+(const Vec2& v) const;
        constexpr Vec2 operator-(const Vec2& v) const;
        constexpr Vec2 operator*(float s) const;
        constexpr Vec2 operator/(float s) const;

        // ������Z�q
        Vec2& operator+=(const Vec2& v);
        Vec2& operator-=(const Vec2& v);
        Vec2& operator*=(float s);
        Vec2& operator/=(float s);
    };

    // �񍀉��Z�q
    inline constexpr Vec2 operator *(float s, const Vec2& v);
}