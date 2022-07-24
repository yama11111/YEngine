#pragma once
struct Vec2
{
    float x;
    float y;

    Vec2() = default; // ��x�N�g��
    constexpr Vec2(const float x, const float y);

    float Length() const;                   // �m����(����)
    constexpr float LengthSquare() const;   // ���� 2��
    Vec2 Normalized() const;                // ���K��
    constexpr bool IsZero() const;          // ��x�N�g����

    constexpr float Dot(const Vec2& v) const; // ����
    float Distance(const Vec2& v) const; // ����

    // �P�����Z�q
    constexpr Vec2 operator+() const;
    constexpr Vec2 operator-() const;
    constexpr Vec2 operator+(const Vec2& v) const;
    constexpr Vec2 operator-(const Vec2& v) const;
    constexpr Vec2 operator*(float s) const;
    constexpr Vec2 operator/(float s) const;

    // ������Z�q
    constexpr Vec2& operator+=(const Vec2& v);
    constexpr Vec2& operator-=(const Vec2& v);
    constexpr Vec2& operator*=(float s);
    constexpr Vec2& operator/=(float s);
};

// �񍀉��Z�q
inline constexpr Vec2 operator *(float s, const Vec2& v);
