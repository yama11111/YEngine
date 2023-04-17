#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <vector>

namespace YMath
{
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
	/// �C�[�Y�C��(���񂾂񑁂�)
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
	/// �C�[�Y�A�E�g(���񂾂�x��)
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
	/// �x�W�G�Ȑ�
	/// </summary>
	/// <param name="points"> : ��_�̔z�� (1�_�ȏ�K�{)</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <returns>���̊����̎��̒l</returns>
	Vector3 Bezier(const std::vector<Vector3>& points, const float ratio);

	/// <summary>
	/// �X�v���C���Ȑ�
	/// </summary>
	/// <param name="points"> : ��_�̔z�� (4�_�ȏ�K�{)</param>
	/// <param name="section"> : �z��̈ʒu (point��point�̊�)</param>
	/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
	/// <returns>���̊����̎��̒l</returns>
	Vector3 Spline(const std::vector<Vector3>& points, const size_t section, const float ratio);

	/// <summary>
	/// �C�[�Y�C��[�x�W�G�Ȑ�ver](���񂾂񑁂�)
	/// </summary>
	/// <param name="points"></param>
	/// <param name="ratio"></param>
	/// <param name="exponent"></param>
	/// <returns></returns>
	Vector3 EaseInBezier(const std::vector<Vector3>& points, const float ratio, const float exponent);

	/// <summary>
	/// �C�[�Y�A�E�g[�x�W�G�Ȑ�ver](���񂾂�x��)
	/// </summary>
	/// <param name="points"></param>
	/// <param name="ratio"></param>
	/// <param name="exponent"></param>
	/// <returns></returns>
	Vector3 EaseOutBezier(const std::vector<Vector3>& points, const float ratio, const float exponent);


	// �C�[�W���O�N���X
	template<typename T>
	class Ease
	{
	private:
		// �����l
		T start_ = T();
		// �ŏI�l
		T end_ = T();
		// �ɋ}(�w��)
		float exponent_ = 0.0f;
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="start"> : �����l</param>
		/// <param name="end"> : �ŏI�l</param>
		/// <param name="exponent"> : �w��(�ɋ})</param>
		void Initialize(const T& start, const T& end, const float exponent);
		/// <summary>
		/// �C�[�Y�C��(���񂾂񑁂�)
		/// </summary>
		/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
		/// <returns>���̊����̎��̒l</returns>
		T In(const float ratio);
		/// <summary>
		/// �C�[�Y�A�E�g(���񂾂�x��)
		/// </summary>
		/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
		/// <returns>���̊����̎��̒l</returns>
		T Out(const float ratio);
	public:
		// �����l�ݒ�
		void SetStart(const T& start) { start_ = start; };
		// �ŏI�l�ݒ� 
		void SetEnd(const T& end) { end_ = end; };
		// �ɋ}�ݒ�
		void SetExponent(const float exponent) { exponent_ = exponent; }
	public:
		// �����l�ݒ�
		T SetStart() const { return start_; };
		// �ŏI�l�ݒ� 
		T SetEnd() const { return end_; };
		// �ɋ}�ݒ�
		float SetExponent() const { return exponent_; }
	};


	// �Ȑ��C�[�W���O�N���X
	class BezierEase
	{
	private:
		// �l
		std::vector<Vector3> points_{};
		// �ɋ}(�w��)
		float exponent_ = 0.0f;
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="points"> : ��_�̔z�� (1�_�ȏ�K�{)</param>
		/// <param name="exponent"> : �w��(�ɋ})</param>
		void Initialize(const std::vector<Vector3>& points, const float exponent);
	public:
		/// <summary>
		/// �C�[�Y�C��(���񂾂񑁂�)
		/// </summary>
		/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
		/// <returns>���̊����̎��̒l</returns>
		Vector3 In(const float ratio);
		/// <summary>
		/// �C�[�Y�A�E�g(���񂾂�x��)
		/// </summary>
		/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
		/// <returns>���̊����̎��̒l</returns>
		Vector3 Out(const float ratio);
	public:
		// �����l�ݒ�
		void SetStart(const std::vector<Vector3>& points) { points_ = points; };
		// �ɋ}�ݒ�
		void SetExponent(const float exponent) { exponent_ = exponent; }
	};
}
