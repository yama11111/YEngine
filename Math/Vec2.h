#pragma once

namespace Math
{
    struct Vec2
    {
    public:
        float x_;
        float y_;
    public:
        // コンストラクタ(零ベクトル)
        Vec2();
        // コンストラクタ(引数有)
        Vec2(float x, float y);
    public:
        // ノルム(長さ)
        float Length() const;
        // 長さ 2乗
        constexpr float LengthSquare() const;
        // 正規化
        Vec2 Normalized() const;
        // 零ベクトルか
        constexpr bool IsZero() const;
        // 内積
        constexpr float Dot(const Vec2& v) const;
        // 距離
        float Distance(const Vec2& v) const;
    public:
        // 単項演算子
        Vec2 operator+() const;
        Vec2 operator-() const;
        // 代入演算子
        Vec2& operator+=(const Vec2& v);
        Vec2& operator-=(const Vec2& v);
        Vec2& operator*=(float s);
        Vec2& operator/=(float s);
        // 比較演算子
        bool operator==(const Vec2& v);
        bool operator!=(const Vec2& v);
    };
    // 二項演算子
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