#pragma once

namespace YMath
{
    struct Vector2
    {
    public:
        float x;
        float y;
    public:
        // コンストラクタ(零ベクトル)
        Vector2();
        // コンストラクタ(引数有)
        Vector2(float x, float y);
    public:
        // ノルム(長さ)
        float Length() const;
        // 長さ 2乗
        constexpr float LengthSquare() const;
        // 正規化
        Vector2 Normalized() const;
        // 零ベクトルか
        constexpr bool IsZero() const;
        // 内積
        constexpr float Dot(const Vector2& v) const;
        // 距離
        float Distance(const Vector2& v) const;
    public:
        // 単項演算子
        Vector2 operator+() const;
        Vector2 operator-() const;
        // 代入演算子
        Vector2& operator+=(const Vector2& v);
        Vector2& operator-=(const Vector2& v);
        Vector2& operator*=(float s);
        Vector2& operator/=(float s);
        // 比較演算子
        bool operator==(const Vector2& v);
        bool operator!=(const Vector2& v);
    };
    // 二項演算子
    inline Vector2 operator+(const Vector2& v1, const Vector2& v2)
    {
        return{ v1.x + v2.x, v1.y + v2.y };
    }
    inline Vector2 operator-(const Vector2& v1, const Vector2& v2)
    {
        return{ v1.x - v2.x, v1.y - v2.y };
    }
    inline Vector2 operator*(const Vector2& v, float s)
    {
        return{ v.x * s, v.y * s };
    }
    inline Vector2 operator*(float s, const Vector2& v)
    {
        return { s * v.x, s * v.y };
    }
    inline Vector2 operator/(const Vector2& v, float s)
    {
        return{ v.x / s, v.y / s };
    }

    using Vec2 = Vector2;
}