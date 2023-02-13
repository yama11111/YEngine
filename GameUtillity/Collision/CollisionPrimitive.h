#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace YGame
{
	// レイ
	class Ray 
	{
	public:
		// 初期位置
		YMath::Vector3 start_ = { 0,0,0 };
		// 方向
		YMath::Vector3 direction_ = { 1,0,0 };
	public:
		// 方向設定 (正規化するように)
		void SafeSetDirection(const YMath::Vector3& direction);
	};

	// 平面
	class Plane 
	{
	public:
		// 法線ベクトル
		YMath::Vector3 normal_ = { 0.0f,+1.0f,0.0f };
		// 原点からの距離
		float distance_ = 0.0f;
	public:
		// 法線設定 (正規化するように)
		void SafeSetNormal(const YMath::Vector3& normal);
	};

	// 三角形
	class Triangle 
	{
	public:
		// 頂点座標
		YMath::Vector3 p0_;
		YMath::Vector3 p1_;
		YMath::Vector3 p2_;
		// 法線ベクトル
		YMath::Vector3 normal_;
	public:
		// 法線設定 (正規化するように)
		void SafeSetNormal(const YMath::Vector3& normal);
		// 法線の計算 (現在の3点から)
		void CalcNormal();
	};

	// 球
	class Sphere
	{
	public:
		// 中心座標
		YMath::Vector3 center_ = { 0.0f,0.0f,0.0f };
		// 半径
		float radius_ = 0.0f;
	public:
		// 半径設定 (負の値にならないように)
		void SafeSetRadius(const float rad);
	};
	
	//     線 × 平面
	bool CollisionRayPlane(const Ray& ray, const Plane& plane);
	
	//     線 × 三角形
	bool CollisionRayTriangle(const Ray& ray, const Triangle& triangle);

	//     線 × 球
	bool CollisionRaySphere(const Ray& ray, const Sphere& sphere);

	//   平面 × 球
	bool CollisionPlaneSphere(const Plane& plane, const Sphere& sphere);

	// 三角形 × 球
	bool CollisionTriangleSphere(const Triangle& triangle, const Sphere& sphere);
}
