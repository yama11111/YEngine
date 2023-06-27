#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace YGame
{
	// レイ
	struct Ray 
	{
	
	private:
		
		// 初期位置
		YMath::Vector3 start_ = { 0,0,0 };
		
		// 方向
		YMath::Vector3 direction_ = { 1,0,0 };
	
	public:
		
		// レイ開始位置設定
		void SetRayStart(const YMath::Vector3& start);

		// レイ方向設定
		void SetRayDirection(const YMath::Vector3& direction);

	public:
		
		// レイ開始位置取得
		inline YMath::Vector3 GetRayStart() const { return start_; }
		
		// レイ方向取得
		inline YMath::Vector3 GetRayDirection() const { return direction_; }

	public:

		Ray() = default;

		Ray(const YMath::Vector3& start, const YMath::Vector3& direction);

		virtual ~Ray() = default;

	};

	// 平面
	struct Plane 
	{
	
	private:
		
		// 法線ベクトル
		YMath::Vector3 normal_ = { 0.0f,+1.0f,0.0f };
		
		// 原点からの距離
		float distance_ = 0.0f;

	public:

		// 平面法線設定
		void SetPlaneNormal(const YMath::Vector3& normal);
		
		// 平面の原点からの位置設定
		void SetPlaneDistance(const float distance);
	
	public:

		// 平面法線取得
		inline YMath::Vector3 GetPlaneNormal() const { return normal_; }

		// 平面の原点からの位置取得
		inline float GetPlaneDistance() const { return distance_; }

	public:

		Plane() = default;

		Plane(const YMath::Vector3& normal, const float distance);

		virtual ~Plane() = default;

	};

	// 三角形
	struct Triangle 
	{
	
	private:
		
		// 頂点座標
		YMath::Vector3 p0_;
		YMath::Vector3 p1_;
		YMath::Vector3 p2_;
		
		// 法線ベクトル
		YMath::Vector3 normal_;
	
	public:
		
		// 三角形位置設定
		void SetTrianglePos(const YMath::Vector3& p0, const YMath::Vector3& p1, const YMath::Vector3& p2);

		// 三角形法線設定
		void SetTriangleNormal(const YMath::Vector3& normal);
		
		// 三角形法線の計算 (現在の3点から)
		void CalcTriangleNormal();

	public:

		// 三角形位置取得
		YMath::Vector3 GetTrianglePos(const size_t index) const;

		// 三角形法線設定
		inline YMath::Vector3 GetTriangleNormal() const { return normal_; }

	public:

		Triangle() = default;
		
		Triangle(const YMath::Vector3& p0, const YMath::Vector3& p1, const YMath::Vector3& p2);
		
		Triangle(const YMath::Vector3& p0, const YMath::Vector3& p1, const YMath::Vector3& p2, const YMath::Vector3& normal);

		virtual ~Triangle() = default;

	};

	// 球
	struct Sphere
	{
	
	private:
		
		// 中心座標
		YMath::Vector3 center_ = { 0.0f,0.0f,0.0f };
		
		// 半径
		float radius_ = 0.0f;
	
	public:
		
		// 球の中心座標設定
		void SetSphereCenter(const YMath::Vector3& center);

		// 球の半径設定
		void SetSphereRadius(const float radius);

	public:

		// 球の中心座標取得
		inline YMath::Vector3 GetSphereCenter() const { return center_; }

		// 球の半径取得
		inline float GetSphereRadius() const { return radius_; }

	public:

		Sphere() = default;

		Sphere(const YMath::Vector3& center, const float radius);

		virtual ~Sphere() = default;
	
	};

	// 四角形 [2D]
	struct Box2D
	{

	private:

		// 中心座標
		YMath::Vector2 center_ = { 0.0f,0.0f };

		// 半径サイズ
		YMath::Vector2 radSize_ = { 0.0f,0.0f };

	public:

		// 四角形[2D]中心座標設定
		void SetBox2DCenter(const YMath::Vector2& center);

		// 四角形[2D]半径サイズ設定
		void SetBox2DRadSize(const YMath::Vector2& radSize);

	public:

		// 四角形[2D]中心座標設定
		YMath::Vector2 GetBox2DCenter() const { return center_; }

		// 四角形[2D]半径サイズ設定
		YMath::Vector2 GetBox2DRadSize() const { return radSize_; }

	public:

		Box2D() = default;

		Box2D(const YMath::Vector2& center, const YMath::Vector2& radSize);

		virtual ~Box2D() = default;

	};

	
	// 線 × 平面
	bool CollisionRayPlane(const Ray& ray, const Plane& plane);
	bool CollisionRayPlane(const Ray& ray, const Plane& plane, float& distance, YMath::Vector3& inter);
	
	// 線 × 三角形
	bool CollisionRayTriangle(const Ray& ray, const Triangle& triangle);

	// 線 × 球
	bool CollisionRaySphere(const Ray& ray, const Sphere& sphere);

	// 平面 × 球
	bool CollisionPlaneSphere(const Plane& plane, const Sphere& sphere);

	// 三角形 × 球
	bool CollisionTriangleSphere(const Triangle& triangle, const Sphere& sphere);

	// 球 × 球
	bool CollisionSphereSphere(const Sphere& sphere1, const Sphere& sphere2);


	// 四角形[2D] × 四角形[2D]
	bool CollisionBoxBox2D(const Box2D& box1, const Box2D& box2);

}
