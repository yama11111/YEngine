#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "BasePrimitiveCollider.h"
#include <array>

namespace YMath
{
	// レイ
	class RayCollider final:
		public BasePrimitiveCollider
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="direction"> : 向き</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint, 
			const Vector3& direction,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="direction"> : 向き</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint, 
			Vector3* pVelocity,
			const Vector3& direction,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>衝突したか</returns>
		bool CheckCollision(const BasePrimitiveCollider& other) const override;

	public:

		/// <summary>
		/// 初期位置
		/// </summary>
		/// <returns>初期位置</returns>
		Vector3 Start() const;

		/// <summary>
		/// 方向
		/// </summary>
		/// <returns>方向</returns>
		inline Vector3 Direction() const { return direction_.Normalized(); }
	
	public:

		RayCollider() = delete;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="direction"> : 向き</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		RayCollider(
			Vector3* pFollowPoint,
			const Vector3& direction,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="direction"> : 向き</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		RayCollider(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const Vector3& direction,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		virtual ~RayCollider() = default;

	protected:

		// 方向
		Vector3 direction_ = { 1,0,0 };

	protected:

		// 線 × 平面
		bool CheckConcreteCollision(const PlaneCollider& other) const override;

		// 線 × 三角形
		bool CheckConcreteCollision(const TriangleCollider& other) const override;

		// 線 × 球
		bool CheckConcreteCollision(const SphereCollider& other) const override;

	};

	// 平面
	class PlaneCollider final:
		public BasePrimitiveCollider
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="normal"> : 法線</param>
		/// <param name="distance"> : 距離</param>
		/// <param name="rectangle"> : 縦横サイズ</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			const Vector3& normal, 
			const float distance, 
			const Vector2& rectangle, 
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="normal"> : 法線</param>
		/// <param name="distance"> : 距離</param>
		/// <param name="rectangle"> : 縦横サイズ</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const Vector3& normal, 
			const float distance, 
			const Vector2& rectangle, 
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>衝突したか</returns>
		bool CheckCollision(const BasePrimitiveCollider& other) const override;

	public:

		/// <summary>
		/// 法線
		/// </summary>
		/// <returns>法線</returns>
		inline Vector3 Normal() const { return normal_.Normalized(); }

		/// <summary>
		/// 距離
		/// </summary>
		/// <returns>距離</returns>
		inline float Distance() const { return distance_; }
	
	public:

		PlaneCollider() = delete;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="normal"> : 法線</param>
		/// <param name="distance"> : 距離</param>
		/// <param name="rectangle"> : 縦横サイズ</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		PlaneCollider(
			Vector3* pFollowPoint,
			const Vector3& normal,
			const float distance,
			const Vector2& rectangle,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="normal"> : 法線</param>
		/// <param name="distance"> : 距離</param>
		/// <param name="rectangle"> : 縦横サイズ</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		PlaneCollider(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const Vector3& normal,
			const float distance,
			const Vector2& rectangle,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);


		virtual ~PlaneCollider() = default;

	protected:

		// 法線ベクトル
		Vector3 normal_ = { 0.0f,+1.0f,0.0f };

		// 原点からの距離
		float distance_ = 0.0f;

		// 縦横サイズ
		Vector2 rectangle_ = {};

	protected:

		// 線 × 平面
		bool CheckConcreteCollision(const RayCollider& other) const override;

		// 平面 × 球
		bool CheckConcreteCollision(const SphereCollider& other) const override;
	};

	// 三角形
	class TriangleCollider final:
		public BasePrimitiveCollider
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="vertices"> : 頂点位置</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint, 
			const std::array<Vector3, 3>& vertices, 
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="vertices"> : 頂点位置</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const std::array<Vector3, 3>& vertices,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		/// <summary>
		/// 三角形法線の計算 (現在の3点から)
		/// </summary>
		void CalcTriangleNormal();

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>衝突したか</returns>
		bool CheckCollision(const BasePrimitiveCollider& other) const override;

	public:
		
		/// <summary>
		/// 三角形頂点位置
		/// </summary>
		/// <param name="index">インデックス</param>
		/// <returns>三角形頂点位置</returns>
		YMath::Vector3 VertexPos(const size_t index) const;
		
		/// <summary>
		/// 法線
		/// </summary>
		/// <returns>法線</returns>
		inline YMath::Vector3 Normal() const { return normal_; }

	public:

		TriangleCollider() = delete;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="vertices"> : 頂点位置</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		TriangleCollider(
			Vector3* pFollowPoint,
			const std::array<Vector3, 3>& vertices,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="vertices"> : 頂点位置</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		TriangleCollider(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const std::array<Vector3, 3>& vertices,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		virtual ~TriangleCollider() = default;

	protected:

		// 頂点座標
		std::array<Vector3, 3> vertices_;

		// 法線ベクトル
		Vector3 normal_;

	protected:

		// 線 × 三角形
		bool CheckConcreteCollision(const RayCollider& other) const override;

		// 三角形 × 球
		bool CheckConcreteCollision(const SphereCollider& other) const override;

	};

	// 球
	class SphereCollider final:
		public BasePrimitiveCollider
	{

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			const float radius, 
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const float radius, 
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);
		
		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>衝突したか</returns>
		bool CheckCollision(const BasePrimitiveCollider& other) const override;

	public:

		/// <summary>
		/// 中心点
		/// </summary>
		/// <returns>中心点</returns>
		YMath::Vector3 Center() const;
		
		/// <summary>
		/// 半径
		/// </summary>
		/// <returns>半径</returns>
		inline float Radius() const { return radius_; }

	public:

		SphereCollider() = delete;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		SphereCollider(
			Vector3* pFollowPoint,
			const float radius,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		SphereCollider(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const float radius,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		virtual ~SphereCollider() = default;

	protected:

		// 半径
		float radius_ = 0.0f;

	protected:

		// 線 × 球
		bool CheckConcreteCollision(const RayCollider& other) const override;

		// 平面 × 球
		bool CheckConcreteCollision(const PlaneCollider& other) const override;

		// 三角形 × 球
		bool CheckConcreteCollision(const TriangleCollider& other) const override;

		// 球 × 球
		bool CheckConcreteCollision(const SphereCollider& other) const override;

	};

	// 四角形 [2D]
	class Box2DCollider final:
		public BasePrimitiveCollider
	{

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="rectSize"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			const Vector2& rectSize,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="rectSize"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const Vector2& rectSize,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>衝突したか</returns>
		bool CheckCollision(const BasePrimitiveCollider& other) const override;

	public:
		
		/// <summary>
		/// 中心座標
		/// </summary>
		/// <returns></returns>
		YMath::Vector2 Center() const;
		
		/// <summary>
		/// 半径
		/// </summary>
		/// <returns>半径</returns>
		inline YMath::Vector2 RectSize() const { return rectSize_; }

	public:

		Box2DCollider() = delete;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="rectSize"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		Box2DCollider(	
			Vector3* pFollowPoint,
			const Vector2& rectSize,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="rectSize"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		Box2DCollider(	
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const Vector2& rectSize,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		virtual ~Box2DCollider() = default;

	protected:

		// 半径
		YMath::Vector2 rectSize_ = { 0.0f,0.0f };

	protected:

		// 四角形[2D] × 四角形[2D]
		bool CheckConcreteCollision(const Box2DCollider& other) const override;

	};


	// 線 × 平面
	static bool CollisionRayPlane(const RayCollider& ray, const PlaneCollider& plane);
	//static bool CollisionRayPlane(const RayCollider& ray, const PlaneCollider& plane, float& distance, YMath::Vector3& inter);

	// 線 × 三角形
	static bool CollisionRayTriangle(const RayCollider& ray, const TriangleCollider& triangle);

	// 線 × 球
	static bool CollisionRaySphere(const RayCollider& ray, const SphereCollider& sphere);

	// 平面 × 球
	static bool CollisionPlaneSphere(const PlaneCollider& plane, const SphereCollider& sphere);

	// 三角形 × 球
	static bool CollisionTriangleSphere(const TriangleCollider& triangle, const SphereCollider& sphere);

	// 球 × 球
	static bool CollisionSphereSphere(const SphereCollider& sphere1, const SphereCollider& sphere2);

	// 四角形[2D] × 四角形[2D]
	static bool CollisionBoxBox2D(const Box2DCollider& box1, const Box2DCollider& box2);

}
