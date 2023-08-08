#pragma once
#include <vector>

namespace YMath
{
	// �x�W�G�Ȑ��C�[�W���O�N���X
	template<typename T>
	class BezierEase
	{
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="points"> : ��_�̔z�� (1�_�ȏ�K�{)</param>
		/// <param name="exponent"> : �w��(�ɋ})</param>
		void Initialize(const std::vector<T>& points, const float exponent);
	
	public:

		/// <summary>
		/// �C�[�Y�C��
		/// (���񂾂񑁂�)
		/// </summary>
		/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
		/// <returns>���̊����̎��̒l</returns>
		T In(const float ratio) const;
		
		/// <summary>
		/// �C�[�Y�A�E�g
		/// (���񂾂�x��)
		/// </summary>
		/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
		/// <returns>���̊����̎��̒l</returns>
		T Out(const float ratio) const;

		/// <summary>
		/// �C�[�Y�C���A�E�g
		/// (���񂾂񑁂� �� ���񂾂�x��)
		/// </summary>
		/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
		/// <param name="controlPoint"> : ����_</param>
		/// <returns>���̊����̎��̒l</returns>
		T InOut(const float ratio, const float controlPoint = 0.5f) const;

		/// <summary>
		/// �C�[�Y�A�E�g�C��
		/// (���񂾂�x�� �� ���񂾂񑁂�)
		/// </summary>
		/// <param name="ratio"> : ���� (��{ 0.0 ~ 1.0)</param>
		/// <param name="controlPoint"> : ����_</param>
		/// <returns>���̊����̎��̒l</returns>
		T OutIn(const float ratio, const float controlPoint = 0.5f) const;
	
	public:
		
		/// <summary>
		/// ��_�ݒ�
		/// </summary>
		/// <param name="points"> : ��_�̔z��</param>
		void SetPoints(const std::vector<T>& points) { points_ = points; };
		
		/// <summary>
		/// �ɋ}�ݒ�
		/// </summary>
		/// <param name="exponent"> : �ɋ}</param>
		void SetExponent(const float exponent) { exponent_ = exponent; }
	
	public:

		/// <summary>
		/// ��_�擾
		/// </summary>
		/// <returns>��_�̔z��</returns>
		std::vector<T> Points() const { return points_; };
		
		/// <summary>
		/// �ɋ}�擾
		/// </summary>
		/// <returns>�ɋ}</returns>
		float Exponent() const { return exponent_; }
	
	private:

		// �l
		std::vector<T> points_{};

		// �ɋ}(�w��)
		float exponent_ = 0.0f;

	};
}
