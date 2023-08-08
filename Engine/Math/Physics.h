#pragma once

namespace YMath
{
	/// <summary>
	/// 速さ計算
	/// </summary>
	/// <param name="accel"> : 加速度</param>
	/// <param name="time"> : 時間</param>
	/// <param name="initiale"> : 初速度</param>
	/// <returns>速度</returns>
	float CalcSpeed(const float acceleration, const float time, const float initiale = 0.0f);

	/// <summary>
	/// 速さ計算 (距離を使う)
	/// </summary>
	/// <param name="accel"> : 加速度</param>
	/// <param name="distance"> : 距離</param>
	/// <param name="initiale"> : 初速度</param>
	/// <returns>速度</returns>
	float CalcSpeedUsingDistance(const float acceleration, const float distance, const float initiale = 0.0f);

	/// <summary>
	/// 加速度計算
	/// </summary>
	/// <param name="speed"> : 速さ</param>
	/// <param name="time"> : 時間</param>
	/// <param name="initiale"> : 初速度</param>
	/// <returns>加速度</returns>
	float CalcAcceleration(const float speed, const float time, const float initiale = 0.0f);

	/// <summary>
	/// 距離計算
	/// </summary>
	/// <param name="accel"> : 加速度</param>
	/// <param name="time"> : 時間</param>
	/// <param name="initiale"> : 初速度</param>
	/// <returns>距離</returns>
	float CalcDistance(const float acceleration, const float time, const float initiale = 0.0f);

	/// <summary>
	/// 距離計算 (速さを使う)
	/// </summary>
	/// <param name="speed"> : 速さ</param>
	/// <param name="time"> : 時間</param>
	/// <param name="initiale"> : 初速度</param>
	/// <returns>距離</returns>
	float CalcDistanceUsingSpeed(const float speed, const float time, const float initiale = 0.0f);

	/// <summary>
	/// 重力加速度計算
	/// </summary>
	/// <param name="time"> : 時間</param>
	/// <returns></returns>
	float CalcGravityAcceleration(const float time);

	/// <summary>
	/// 重力速度計算
	/// </summary>
	/// <param name="time"> : 時間</param>
	/// <param name="initiale"> : 初速度</param>
	/// <returns>重力速度</returns>
	float CalcGravitySpeed(const float time, const float initiale = 0.0f);

	/// <summary>
	/// 距離計算
	/// </summary>
	/// <param name="time"> : 時間</param>
	/// <param name="initiale"> : 初速度</param>
	/// <returns>距離</returns>
	float CalcDistanceUsingGravity(const float time, const float initiale);

	/// <summary>
	/// 抵抗力計算
	/// </summary>
	/// <param name="proportion"> : 比例定数</param>
	/// <param name="speed"> : 速さ</param>
	/// <returns>抵抗力</returns>
	float CalcResistingForce(const float proportion, const float speed);
};

