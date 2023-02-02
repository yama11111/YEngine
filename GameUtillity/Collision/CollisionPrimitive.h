#pragma once
#include "Vec2.h"
#include "Vec3.h"

namespace YCollision
{
	// 平面
	class Plane 
	{
	public:
		// 法線ベクトル
		YMath::Vec3 normal_ = { 0.0f,+1.0f,0.0f };
		// 原点からの距離
		float distance_ = 0.0f;
	public:
		void SafeSetNormal(const YMath::Vec3& normal);
	};

	// 三角形
	class Triangle 
	{
	public:
		// 頂点座標
		YMath::Vec3 p0_;
		YMath::Vec3 p1_;
		YMath::Vec3 p2_;
		// 法線ベクトル
		YMath::Vec3 normal_;
	public:
		void SafeSetNormal(const YMath::Vec3& normal);
	};

	// 球
	class Sphere
	{
	public:
		// 中心座標
		YMath::Vec3 center_ = { 0.0f,0.0f,0.0f };
		// 半径
		float radius_ = 0.0f;
	public:
		void SafeSetRadius(const float rad);
	};
	
	// 平面 × 球
	bool CollisonPlaneSphere(const Plane& plane, const Sphere& sphere);

	// 三角形 × 球
	bool CollisionTriangleSphere(const Triangle& triangle, const Sphere& sphere);
}
