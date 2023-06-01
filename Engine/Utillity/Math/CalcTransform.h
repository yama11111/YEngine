#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

namespace YMath
{
#pragma region �ϊ��n
	
	// ------------ �A�t�B���ϊ� ------------ //
	
	// �g�k�ϊ�
	Matrix4 MatScale(const Vector3& s);
	
	// X����]�ϊ�
	Matrix4 MatRotationX(float angle);
	// Y����]�ϊ�
	Matrix4 MatRotationY(float angle);
	// Z����]�ϊ�
	Matrix4 MatRotationZ(float angle);
	// ��]�ϊ�(Z��X��Y)
	Matrix4 MatRotation(const Vector3& r);

	// ���W�ϊ�
	Matrix4 MatTranslation(const Vector3& t);
	
	// ----- �r���[�v���W�F�N�V�����ϊ� ----- //
	
	// ���s���e�ϊ��s��
	Matrix4 MatOrthoGraphic();
	// �������e�ϊ��s��
	Matrix4 MatPerspective();
	// �r���[�|�[�g�s��
	Matrix4 MatViewPort();
	// �r���[�s��(������W�n)
	Matrix4 MatLookAtLH(const Vector3& eye, const Vector3& target, const Vector3& up);
	
#pragma endregion

	Vector3 MatTransform(const Vector3& v, const Matrix4& m);
	Vector3 operator*(const Vector3& v, const Matrix4& m);

	// Vector3 * Matrix4
	Vector3 MultVec3Mat4(const Vector3& v, const Matrix4& m);
	// Vector4 * Matrix4
	Vector4 MultVec4Mat4(const Vector4& v, const Matrix4& m);
	// �t�s��
	Matrix4 InverceMat4(const Matrix4& m);

	// 2D���W��3D���W
	Vector3 WorldPos(const Vector2& screen, float z, const Matrix4& view, const Matrix4& projection);

	// �p�x����
	Vector3 AdjustAngle(const Vector3& velocity);

	// �r���{�[�h�s��
	Matrix4 BillboardMatrix(const bool isXAxisBillboard, const bool isYAxisBillboard, 
		const Vector3& eye, const Vector3& target, const Vector3& up);
}