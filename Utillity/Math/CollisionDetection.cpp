#include "CollisionDetection.h"
#include <cmath>

using YMath::Vector3;

static const float Epsilon = 1.0e-5f;

#pragma region 線と平面

bool YMath::CollisionRayPlane(
	const Vector3& rayStart, const Vector3& rayDirection,
	const Vector3& planeNormal, const float planeDist)
{
	// 面法線とレイの方向ベクトルの内積
	float d1 = planeNormal.Dot(rayDirection);
	// 裏面には当たらない
	if (d1 > -Epsilon) { return false; }

	// 始点 → 原点 (平面の法線方向)
	// 面法線 と レイの視点座標 (位置ベクトル) の内積
	float d2 = planeNormal.Dot(rayStart);

	// 始点と平面の距離 (平面の法線方向)
	float dist = d2 - planeDist;

	// 始点と平面の距離 (レイ方向)
	float t = dist / -d1;
	// 交点が始点より後ろにある → 当たらない
	if (t < 0) { return false; }

	return true;
}

bool YMath::CollisionRayPlane(
	const Vector3& rayStart, const Vector3& rayDirection, 
	const Vector3& planeNormal, const float planeDist, 
	float& distance, Vector3& inter)
{
	// 面法線とレイの方向ベクトルの内積
	float d1 = planeNormal.Dot(rayDirection);
	// 裏面には当たらない
	if (d1 > -Epsilon) { return false; }

	// 始点 → 原点 (平面の法線方向)
	// 面法線 と レイの視点座標 (位置ベクトル) の内積
	float d2 = planeNormal.Dot(rayStart);

	// 始点と平面の距離 (平面の法線方向)
	float dist = d2 - planeDist;

	// 始点と平面の距離 (レイ方向)
	float t = dist / -d1;
	// 交点が始点より後ろにある → 当たらない
	if (t < 0) { return false; }
	
	// 距離
	distance = t;
	// 交点
	inter = rayStart + (t * rayDirection);

	return true;
}

#pragma endregion


#pragma region 線と三角形

bool YMath::CollisionRayTriangle(
	const Vector3& rayStart, const Vector3& rayDirection,
	const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal)
{
	// 三角形の平面
	Vector3 planeNormal = triNormal;
	float planeDist = triNormal.Dot(triPos0);
	float distance = 0.0f;
	Vector3 interPlane;

	// レイ と 平面が当たっているか
	if (CollisionRayPlane(rayStart, rayDirection, planeNormal, planeDist, distance, interPlane) == false)
	{
		return false;
	}

	// レイ と 平面の交点 が 三角形の内側か
	// p0 → p1
	Vector3 pt_p0 = triPos0 - interPlane;
	Vector3 p0_p1 = triPos1 - triPos0;
	Vector3 m1 = pt_p0.Cross(p0_p1);
	// 辺の外側 → 当たらない
	if (m1.Dot(triNormal) < -Epsilon) { return false; }

	// p1 → p2
	Vector3 pt_p1 = triPos1 - interPlane;
	Vector3 p1_p2 = triPos2 - triPos1;
	Vector3 m2 = pt_p1.Cross(p1_p2);
	// 辺の外側 → 当たらない
	if (m2.Dot(triNormal) < -Epsilon) { return false; }

	// p2 → p0
	Vector3 pt_p2 = triPos2 - interPlane;
	Vector3 p2_p0 = triPos2 - triPos0;
	Vector3 m3 = pt_p2.Cross(p2_p0);
	// 辺の外側 → 当たらない
	if (m3.Dot(triNormal) < -Epsilon) { return false; }

	return true;
}

bool YMath::CollisionRayTriangle(
	const Vector3& rayStart, const Vector3& rayDirection,
	const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
	float& distance, Vector3& inter)
{
	// 三角形の平面
	Vector3 planeNormal = triNormal;
	float planeDist = triNormal.Dot(triPos0);
	Vector3 interPlane;

	// レイ と 平面が当たっているか
	if (CollisionRayPlane(rayStart, rayDirection, planeNormal, planeDist, distance, interPlane) == false) 
	{
		return false; 
	}

	// レイ と 平面の交点 が 三角形の内側か
	// p0 → p1
	Vector3 pt_p0 = triPos0 - interPlane;
	Vector3 p0_p1 = triPos1 - triPos0;
	Vector3 m1 = pt_p0.Cross(p0_p1);
	// 辺の外側 → 当たらない
	if (m1.Dot(triNormal) < -Epsilon) { return false; }

	// p1 → p2
	Vector3 pt_p1 = triPos1 - interPlane;
	Vector3 p1_p2 = triPos2 - triPos1;
	Vector3 m2 = pt_p1.Cross(p1_p2);
	// 辺の外側 → 当たらない
	if (m2.Dot(triNormal) < -Epsilon) { return false; }
	
	// p2 → p0
	Vector3 pt_p2 = triPos2 - interPlane;
	Vector3 p2_p0 = triPos2 - triPos0;
	Vector3 m3 = pt_p2.Cross(p2_p0);
	// 辺の外側 → 当たらない
	if (m3.Dot(triNormal) < -Epsilon) { return false; }

	// 内側
	inter = interPlane;

	return true;
}

#pragma endregion


#pragma region 線と球

bool YMath::CollisionRaySphere(
	const Vector3& rayStart, const Vector3& rayDirection,
	const Vector3& sphereCenter, const float sphereRad)
{
	Vector3 m = rayStart - sphereCenter;
	float b = m.Dot(rayDirection);
	float c = m.Dot(m) - (sphereRad * sphereRad);
	// レイの始点 が 球の外側 (c > 0) && レイ が 球 から離れていく方向 (b > 0) → 当たらない
	if (c > 0.0f && b > 0.0f) { return false; }

	float discr = b * b - c;
	// 負 → レイ が 球 を外れている → 当たらない
	if (discr < 0.0f) { return false; }

	// 交差
	return true;
}
bool YMath::CollisionRaySphere(
	const Vector3& rayStart, const Vector3& rayDirection,
	const Vector3& sphereCenter, const float sphereRad,
	float& distance, Vector3& start, Vector3& end)
{
	//Vector3 p = sphereCenter - rayDirection;

	//float a = rayDirection.Dot(rayDirection);
	//if (a == 0.0f) { return false; }
	//float b = rayDirection.Dot(p);
	//float c = p.Dot(p) - (sphereRad * sphereRad);

	//float s = b * b - a * c;
	//if (s < 0.0f) { return false; }

	//float a1 = (b - sqrtf(s)) / a;
	//float a2 = (b + sqrtf(s)) / a;
	//if (a1 < 0.0f || a2 < 0.0f) { return false; }

	//start = rayPos + (a1 * rayVelo);
	//end = rayPos + (a2 * rayVelo);


	Vector3 m = rayStart - sphereCenter;
	float b = m.Dot(rayDirection);
	float c = m.Dot(m) - (sphereRad * sphereRad);
	// レイの始点 が 球の外側 (c > 0) && レイ が 球 から離れていく方向 (b > 0) → 当たらない
	if (c > 0.0f && b > 0.0f) { return false; }

	float discr = b * b - c;
	// 負 → レイ が 球 を外れている → 当たらない
	if (discr < 0.0f) { return false; }

	// 交差
	float ts = -b - sqrtf(discr); // 始点
	float te = -b + sqrtf(discr); // 終点

	// t が 負 → レイの内側
	if (ts < 0) { ts = 0.0f; }
	if (te < 0) { te = 0.0f; }
	
	// 距離
	distance = ts;
	//distance = te;

	// 交差点
	start = rayStart + (ts * rayDirection); // 始点
	end	  = rayStart + (te * rayDirection); // 終点

	return true;
}

#pragma endregion


#pragma region 平面と球

bool YMath::CollisionPlaneSphere(
	const Vector3& planeNormal, const float planeDist, 
	const Vector3& sphereCenter, const float sphereRad)
{
	// 原点 → 球 の距離
	float sphereDist = sphereCenter.Dot(planeNormal);
	
	// (球 - 平面) = 球 → 平面 の距離
	float dist = sphereDist - planeDist;
	// (距離(絶対値) > 球の半径) = 当たってない
	if (fabsf(dist) > sphereRad) { return false; }

	return true;
}
bool YMath::CollisionPlaneSphere(
	const Vector3& planeNormal, const float planeDist, 
	const Vector3& sphereCenter, const float sphereRad,
	Vector3& inter)
{
	// 原点 → 球 の距離
	float sphereDist = sphereCenter.Dot(planeNormal);

	// (球 - 平面) = 球 → 平面 の距離
	float dist = sphereDist - planeDist;
	// 距離(絶対値) > 球の半径 = 当たってない
	if (fabsf(dist) > sphereRad) { return false; }

	// 疑似交点 (平面上の最近接点)
	inter = -dist * planeNormal + sphereCenter;

	return true;
}

#pragma endregion


#pragma region 三角形と球

static YMath::Vector3 ClosestPointTriangle(const Vector3& point, const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2)
{
	// p0 の 外側 か
	Vector3 p0_p1 = triPos1 - triPos0;
	Vector3 p0_p2 = triPos2 - triPos0;
	Vector3 p0_pt = point - triPos0;

	float d1 = p0_p1.Dot(p0_pt);
	float d2 = p0_p2.Dot(p0_pt);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0 が 最近傍
		return triPos0;
	}

	// p1 の 外側 か
	Vector3 p1_pt = point - triPos1;

	float d3 = p0_p1.Dot(p1_pt);
	float d4 = p0_p2.Dot(p1_pt);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// p1 が 最近傍
		return triPos1;
	}

	// p0_p1 の 内側か
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		// p0_p1 上に対する射影を返す
		float v = d1 / (d1 - d3);
		return triPos0 + v * p0_p1;
	}

	// p2 の 外側か
	Vector3 p2_pt = point - triPos2;

	float d5 = p0_p1.Dot(p2_pt);
	float d6 = p0_p2.Dot(p2_pt);
	if (d6 >= 0.0f && d5 <= d6)
	{
		// p2 が 最近傍
		return triPos2;
	}

	// p0_p2 の 内側か 
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		// p0_p2 上に対する射影を返す
		float w = d2 / (d2 - d6);
		return triPos0 + w * p0_p2;
	}

	// p1_p2 の 内側か
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		// p1_p2 上に対する射影を返す
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		return triPos1 + w * (triPos2 - triPos1);
	}


	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	return triPos0 + p0_p1 * v + p0_p2 * w;
}

bool YMath::CollisionTriangleSphere(
	const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
	const Vector3& sphereCenter, const float sphereRad)
{
	// 球 の 三角形上 の 最近接点
	Vector3 closest = ClosestPointTriangle(sphereCenter, triPos0, triPos1, triPos2);
	
	// 球 → 最近接点
	Vector3 v = closest - sphereCenter;
	// (球 → 最近接点) ^ 2 > 球の半径 ^ 2 = 当たってない
	if (v.Dot(v) > sphereRad * sphereRad) { return false; }

	return true;
}
bool YMath::CollisionTriangleSphere(
	const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
	const Vector3& sphereCenter, const float sphereRad, 
	Vector3& inter)
{
	// 球 の 三角形上 の 最近接点
	Vector3 closest = ClosestPointTriangle(sphereCenter, triPos0, triPos1, triPos2);

	// 球 → 最近接点
	Vector3 v = closest - sphereCenter;
	// (球 → 最近接点) ^ 2 > 球の半径 ^ 2 = 当たってない
	if (v.Dot(v) > sphereRad * sphereRad) { return false; }

	// 疑似交点 (三角形上の最近接点)
	inter = closest;

	return true;
}

#pragma endregion
