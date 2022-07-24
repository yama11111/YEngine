#pragma once
struct Vec2
{
    float x;
    float y;

    Vec2() = default; // 零ベクトル
    constexpr Vec2(const float x, const float y);

    float Length() const;                   // ノルム(長さ)
    constexpr float LengthSquare() const;   // 長さ 2乗
    Vec2 Normalized() const;                // 正規化
    constexpr bool IsZero() const;          // 零ベクトルか

    constexpr float Dot(const Vec2& v) const; // 内積
    float Distance(const Vec2& v) const; // 距離

    // 単項演算子
    constexpr Vec2 operator+() const;
    constexpr Vec2 operator-() const;
    constexpr Vec2 operator+(const Vec2& v) const;
    constexpr Vec2 operator-(const Vec2& v) const;
    constexpr Vec2 operator*(float s) const;
    constexpr Vec2 operator/(float s) const;

    // 代入演算子
    constexpr Vec2& operator+=(const Vec2& v);
    constexpr Vec2& operator-=(const Vec2& v);
    constexpr Vec2& operator*=(float s);
    constexpr Vec2& operator/=(float s);
};

// 二項演算子
inline constexpr Vec2 operator *(float s, const Vec2& v);
