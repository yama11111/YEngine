#pragma once

namespace YMath
{
	/// <summary>
	/// �����v�Z
	/// </summary>
	/// <param name="accel"> : �����x</param>
	/// <param name="time"> : ����</param>
	/// <param name="initiale"> : �����x</param>
	/// <returns>���x</returns>
	float CalcSpeed(const float acceleration, const float time, const float initiale = 0.0f);

	/// <summary>
	/// �����v�Z (�������g��)
	/// </summary>
	/// <param name="accel"> : �����x</param>
	/// <param name="distance"> : ����</param>
	/// <param name="initiale"> : �����x</param>
	/// <returns>���x</returns>
	float CalcSpeedUsingDistance(const float acceleration, const float distance, const float initiale = 0.0f);

	/// <summary>
	/// �����x�v�Z
	/// </summary>
	/// <param name="speed"> : ����</param>
	/// <param name="time"> : ����</param>
	/// <param name="initiale"> : �����x</param>
	/// <returns>�����x</returns>
	float CalcAcceleration(const float speed, const float time, const float initiale = 0.0f);

	/// <summary>
	/// �����v�Z
	/// </summary>
	/// <param name="accel"> : �����x</param>
	/// <param name="time"> : ����</param>
	/// <param name="initiale"> : �����x</param>
	/// <returns>����</returns>
	float CalcDistance(const float acceleration, const float time, const float initiale = 0.0f);

	/// <summary>
	/// �����v�Z (�������g��)
	/// </summary>
	/// <param name="speed"> : ����</param>
	/// <param name="time"> : ����</param>
	/// <param name="initiale"> : �����x</param>
	/// <returns>����</returns>
	float CalcDistanceUsingSpeed(const float speed, const float time, const float initiale = 0.0f);

	/// <summary>
	/// �d�͉����x�v�Z
	/// </summary>
	/// <param name="time"> : ����</param>
	/// <returns></returns>
	float CalcGravityAcceleration(const float time);

	/// <summary>
	/// �d�͑��x�v�Z
	/// </summary>
	/// <param name="time"> : ����</param>
	/// <param name="initiale"> : �����x</param>
	/// <returns>�d�͑��x</returns>
	float CalcGravitySpeed(const float time, const float initiale = 0.0f);

	/// <summary>
	/// �����v�Z
	/// </summary>
	/// <param name="time"> : ����</param>
	/// <param name="initiale"> : �����x</param>
	/// <returns>����</returns>
	float CalcDistanceUsingGravity(const float time, const float initiale);

	/// <summary>
	/// ��R�͌v�Z
	/// </summary>
	/// <param name="proportion"> : ���萔</param>
	/// <param name="speed"> : ����</param>
	/// <returns>��R��</returns>
	float CalcResistingForce(const float proportion, const float speed);
};

