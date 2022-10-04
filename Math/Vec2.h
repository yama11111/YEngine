#pragma once

namespace Math
{
    struct Vec2
    {
    public:
        float x;
        float y;
    public:
        Vec2(); // 零ベクトル
        Vec2(float x, float y);

        float Length() const;                   // ノルム(長さ)
        constexpr float LengthSquare() const;   // 長さ 2乗
        Vec2 Normalized() const;                // 正規化
        constexpr bool IsZero() const;          // 零ベクトルか

        constexpr float Dot(const Vec2& v) const; // 内積
        float Distance(const Vec2& v) const; // 距離
    public:
        // 単項演算子
        Vec2 operator+() const;
        Vec2 operator-() const;

        // 代入演算子
        Vec2& operator+=(const Vec2& v);
        Vec2& operator-=(const Vec2& v);
        Vec2& operator*=(float s);
        Vec2& operator/=(float s);
    };

    // 二項演算子
    inline Vec2 operator+(const Vec2& v1, const Vec2& v2);
    inline Vec2 operator-(const Vec2& v1, const Vec2& v2);
    inline Vec2 operator*(const Vec2& v, float s);
    inline Vec2 operator*(float s, const Vec2& v);
    inline Vec2 operator/(const Vec2& v, float s);
}