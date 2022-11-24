#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"
#define PI 3.141592f

namespace Math
{
#pragma region �A�t�B���ϊ�
	// �g�k�ϊ�
	Mat4 MatScale(const Vec3& s);
	
	// X����]�ϊ�
	Mat4 MatRotationX(float angle);
	// Y����]�ϊ�
	Mat4 MatRotationY(float angle);
	// Z����]�ϊ�
	Mat4 MatRotationZ(float angle);
	// ��]�ϊ�(Z��X��Y)
	Mat4 MatRotation(const Vec3& r);

	// ���W�ϊ�
	Mat4 MatTranslation(const Vec3& t);
#pragma endregion

	Vec3 MatTransform(const Vec3& v, const Mat4& m);
	Vec3 operator*(const Vec3& v, const Mat4& m);

	// Vector3 * Matrix4
	Vec3 MultVec3Mat4(const Vec3& v, const Mat4& m);
	// Vector4 * Matrix4
	Vec4 MultVec4Mat4(const Vec4& v, const Mat4& m);
	// �t�s��
	Mat4 InverceMat4(const Mat4& m);

	// ���s���e�ϊ��s��
	Mat4 MatOrthoGraphic();
	// �������e�ϊ��s��
	Mat4 MatPerspective();
	// �r���[�|�[�g�s��
	Mat4 MatViewPort();
	// �r���[�s��(������W�n)
	Mat4 MatLookAtLH(const Vec3& eye, const Vec3& target, const Vec3& up);

	// 2D���W��3D���W
	Vec3 WorldPos(const Vec2& screen, float z, const Mat4& view, const Mat4& projection);

	// �p�x����
	Vec3 AdjustAngle(const Vec3& velocity);
	
	// �A�^������(���~��)
	bool CollRaySphere(
		const Vec3& ray, const Vec3& velocity,
		const Vec3& sphere, const float rad);
	
	// �A�^������(���~��) <�ђʓ_�擾ver>
	bool CollRaySphere(
		const Vec3& ray, const Vec3& velocity,
		const Vec3& sphere, const float rad,
		Vec3& start, Vec3& end);
}