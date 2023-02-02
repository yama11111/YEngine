#include "CollisionDetection.h"
#include <cmath>

using YMath::Vec3;

#pragma region 平面 と 球

bool YMath::CollisonPlaneSphere(
	const Vec3& planeNormal, const float planeDist, 
	const Vec3& sphereCenter, const float sphereRad)
{
	// 原点 → 球 の距離
	float sphereDist = sphereCenter.Dot(planeNormal);
	
	// (球 - 平面) = 球 → 平面 の距離
	float dist = sphereDist - planeDist;

	// (距離(絶対値) > 球の半径) = 当たってない
	if (fabsf(dist) > sphereRad) { return false; }

	return true;
}
bool YMath::CollisonPlaneSphere(
	const Vec3& planeNormal, const float planeDist, 
	const Vec3& sphereCenter, const float sphereRad,
	Vec3& inter)
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


#pragma region 三角形 と 球

static YMath::Vec3 ClosestPointTriangle(const Vec3& point, const Vec3& triPos0, const Vec3& triPos1, const Vec3& triPos2)
{
	// p0 の 外側 か
	Vec3 p0_p1 = triPos1 - triPos0;
	Vec3 p0_p2 = triPos2 - triPos0;
	Vec3 p0_pt = point - triPos0;

	float d1 = p0_p1.Dot(p0_pt);
	float d2 = p0_p2.Dot(p0_pt);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0 が 最近傍
		return triPos0;
	}

	// p1 の 外側 か
	Vec3 p1_pt = point - triPos1;

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
	Vec3 p2_pt = point - triPos2;

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

bool YMath::CollisonTriangleSphere(
	const Vec3& triPos0, const Vec3& triPos1, const Vec3& triPos2, const Vec3& triNormal,
	const Vec3& sphereCenter, const float sphereRad)
{
	// 球 の 三角形上 の 最近接点
	Vec3 closest = ClosestPointTriangle(sphereCenter, triPos0, triPos1, triPos2);
	
	// 球 → 最近接点
	Vec3 v = closest - sphereCenter;
	
	// (球 → 最近接点) ^ 2 > 球の半径 ^ 2 = 当たってない
	if (v.Dot(v) > sphereRad * sphereRad) { return false; }

	return true;
}
bool YMath::CollisonTriangleSphere(
	const Vec3& triPos0, const Vec3& triPos1, const Vec3& triPos2, const Vec3& triNormal,
	const Vec3& sphereCenter, const float sphereRad, 
	Vec3& inter)
{
	// 球 の 三角形上 の 最近接点
	Vec3 closest = ClosestPointTriangle(sphereCenter, triPos0, triPos1, triPos2);

	// 球 → 最近接点
	Vec3 v = closest - sphereCenter;

	// (球 → 最近接点) ^ 2 > 球の半径 ^ 2 = 当たってない
	if (v.Dot(v) > sphereRad * sphereRad) { return false; }

	// 疑似交点 (三角形上の最近接点)
	inter = closest;

	return true;
}

#pragma endregion


#pragma region 線 と 球

bool YMath::CollisonRaySphere(
	const Vec3& rayPos, const Vec3& rayVelo,
	const Vec3& spherePos, const float sphereRad)
{
	Vec3 p = spherePos - rayPos;

	float a = rayVelo.Dot(rayVelo);
	if (a == 0.0f) { return false; }
	float b = rayVelo.Dot(p);
	float c = p.Dot(p) - (sphereRad * sphereRad);

	float s = b * b - a * c;
	if (s < 0.0f) { return false; }

	float a1 = (b - sqrtf(s)) / a;
	float a2 = (b + sqrtf(s)) / a;
	if (a1 < 0.0f || a2 < 0.0f) { return false; }

	return true;
}
bool YMath::CollisonRaySphere(
	const Vec3& rayPos, const Vec3& rayVelo,
	const Vec3& spherePos, const float sphereRad,
	Vec3& start, Vec3& end)
{
	Vec3 p = spherePos - rayPos;

	float a = rayVelo.Dot(rayVelo);
	if (a == 0.0f) { return false; }
	float b = rayVelo.Dot(p);
	float c = p.Dot(p) - (sphereRad * sphereRad);

	float s = b * b - a * c;
	if (s < 0.0f) { return false; }

	float a1 = (b - sqrtf(s)) / a;
	float a2 = (b + sqrtf(s)) / a;
	if (a1 < 0.0f || a2 < 0.0f) { return false; }

	start = rayPos + (a1 * rayVelo);
	end = rayPos + (a2 * rayVelo);

	return true;
}

#pragma endregion