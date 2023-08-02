#pragma once
#include "Vector3.h"
#include <vector>

namespace YMath
{

#pragma region Lerp

	/// <summary>
	/// ���
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="a"> : �����l</param>
	/// <param name="b"> : �ŏI�l</param>
	/// <param name="t"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T Lerp(const T& a, const T& b, const float t);

	/// <summary>
	/// 3�������
	/// </summary>
	/// <param name="v1"> : �����l</param>
	/// <param name="v2"> : �ŏI�l</param>
	/// <param name="t"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <returns>���̊����̎��̒l</returns>
	Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t);

	/// <summary>
	/// �x�W�G�Ȑ�
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : ��_�̔z�� (1�_�ȏ�K�{)</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T Bezier(const std::vector<T>& points, const float ratio);

	/// <summary>
	/// �X�v���C���Ȑ�
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : ��_�̔z�� (2�_�ȏ�K�{)</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T Spline(const std::vector<T>& points, const float ratio);

#pragma endregion

#pragma region Ease

	/// <summary>
	/// �C�[�Y�C��
	/// (���񂾂񑁂�)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="start"> : �����l</param>
	/// <param name="end"> : �ŏI�l</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : �w��(�ɋ})</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T EaseIn(const T& start, const T& end, const float ratio, const float exponent);

	/// <summary>
	/// �C�[�Y�A�E�g
	/// (���񂾂�x��)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="start"> : �����l</param>
	/// <param name="end"> : �ŏI�l</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : �w��(�ɋ})</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T EaseOut(const T& start, const T& end, const float ratio, const float exponent);

	/// <summary>
	/// �C�[�Y�C���A�E�g
	/// (���񂾂񑁂� �� ���񂾂�x��)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="start"> : �����l</param>
	/// <param name="end"> : �ŏI�l</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : �w��(�ɋ})</param>
	/// <param name="controlPoint"> : ����_</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T EaseInOut(const T& start, const T& end, const float ratio, const float exponent, const float controlPoint = 0.5f);

	/// <summary>
	/// �C�[�Y�A�E�g�C��
	/// (���񂾂�x�� �� ���񂾂񑁂�)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="start"> : �����l</param>
	/// <param name="end"> : �ŏI�l</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : �w��(�ɋ})</param>
	/// <param name="controlPoint"> : ����_</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T EaseOutIn(const T& start, const T& end, const float ratio, const float exponent, const float controlPoint = 0.5f);

#pragma endregion

#pragma region BezierEase

	/// <summary>
	/// �C�[�Y�C�� [�x�W�G�Ȑ�ver]
	/// (���񂾂񑁂�)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : ��_�̔z�� (1�_�ȏ�K�{)</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : �w��(�ɋ})</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T BezierEaseIn(const std::vector<T>& points, const float ratio, const float exponent);

	/// <summary>
	/// �C�[�Y�A�E�g [�x�W�G�Ȑ�ver]
	/// (���񂾂�x��)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : ��_�̔z�� (1�_�ȏ�K�{)</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : �w��(�ɋ})</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T BezierEaseOut(const std::vector<T>& points, const float ratio, const float exponent);

	/// <summary>
	/// �C�[�Y�A�E�g [�x�W�G�Ȑ�ver]
	/// (���񂾂񑁂� �� ���񂾂�x��)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : ��_�̔z�� (1�_�ȏ�K�{)</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : �w��(�ɋ})</param>
	/// <param name="controlPoint"> : ����_</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T BezierEaseOutIn(const std::vector<T>& points, const float ratio, const float exponent, const float controlPoint = 0.5f);

	/// <summary>
	/// �C�[�Y�A�E�g [�x�W�G�Ȑ�ver]
	/// (���񂾂�x�� �� ���񂾂񑁂�)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : ��_�̔z�� (1�_�ȏ�K�{)</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : �w��(�ɋ})</param>
	/// <param name="controlPoint"> : ����_</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T BezierEaseInOut(const std::vector<T>& points, const float ratio, const float exponent, const float controlPoint = 0.5f);

#pragma endregion

#pragma region SplineEase

	/// <summary>
	/// �C�[�Y�C�� [�X�v���C���Ȑ�ver]
	/// (���񂾂񑁂�)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : ��_�̔z�� (4�_�ȏ�K�{)</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : �w��(�ɋ})</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T SplineEaseIn(const std::vector<T>& points, const float ratio, const float exponent);

	/// <summary>
	/// �C�[�Y�A�E�g [�X�v���C���Ȑ�ver]
	/// (���񂾂�x��)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : ��_�̔z�� (4�_�ȏ�K�{)</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : �w��(�ɋ})</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T SplineEaseOut(const std::vector<T>& points, const float ratio, const float exponent);

	/// <summary>
	/// �C�[�Y�A�E�g [�X�v���C���Ȑ�ver]
	/// (���񂾂񑁂� �� ���񂾂�x��)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : ��_�̔z�� (1�_�ȏ�K�{)</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : �w��(�ɋ})</param>
	/// <param name="controlPoint"> : ����_</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T SplineEaseOutIn(const std::vector<T>& points, const float ratio, const float exponent, const float controlPoint = 0.5f);

	/// <summary>
	/// �C�[�Y�A�E�g [�X�v���C���Ȑ�ver]
	/// (���񂾂�x�� �� ���񂾂񑁂�)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : ��_�̔z�� (1�_�ȏ�K�{)</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : �w��(�ɋ})</param>
	/// <param name="controlPoint"> : ����_</param>
	/// <returns>���̊����̎��̒l</returns>
	template<typename T>
	T SplineEaseInOut(const std::vector<T>& points, const float ratio, const float exponent, const float controlPoint = 0.5f);

#pragma endregion

}
