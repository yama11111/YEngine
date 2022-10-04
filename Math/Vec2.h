#pragma once

namespace Math
{
    struct Vec2
    {
    public:
        float x;
        float y;
    public:
        Vec2(); // ��x�N�g��
        Vec2(float x, float y);

        float Length() const;                   // �m����(����)
        constexpr float LengthSquare() const;   // ���� 2��
        Vec2 Normalized() const;                // ���K��
        constexpr bool IsZero() const;          // ��x�N�g����

        constexpr float Dot(const Vec2& v) const; // ����
        float Distance(const Vec2& v) const; // ����
    public:
        // �P�����Z�q
        Vec2 operator+() const;
        Vec2 operator-() const;

        // ������Z�q
        Vec2& operator+=(const Vec2& v);
        Vec2& operator-=(const Vec2& v);
        Vec2& operator*=(float s);
        Vec2& operator/=(float s);
    };

    // �񍀉��Z�q
    inline Vec2 operator+(const Vec2& v1, const Vec2& v2);
    inline Vec2 operator-(const Vec2& v1, const Vec2& v2);
    inline Vec2 operator*(const Vec2& v, float s);
    inline Vec2 operator*(float s, const Vec2& v);
    inline Vec2 operator/(const Vec2& v, float s);
}