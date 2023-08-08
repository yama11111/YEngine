#pragma once

namespace YMath
{
	// �C�[�W���O�N���X
	template<typename T>
	class Ease
	{

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="start"> : �����l</param>
		/// <param name="end"> : �ŏI�l</param>
		/// <param name="exponent"> : �w��(�ɋ})</param>
		void Initialize(const T& start, const T& end, const float exponent);
	
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
		/// �����l�ݒ�
		/// </summary>
		/// <param name="start"> : �����l</param>
		void SetStart(const T& start) { start_ = start; };

		/// <summary>
		/// �ŏI�l�ݒ�
		/// </summary>
		/// <param name="end"> : �ŏI�l</param>
		void SetEnd(const T& end) { end_ = end; };

		/// <summary>
		/// �ɋ}�ݒ�
		/// </summary>
		/// <param name="exponent"> : �ɋ}</param>
		void SetExponent(const float exponent) { exponent_ = exponent; }
	
	public:
		
		/// <summary>
		/// �����l�擾
		/// </summary>
		/// <returns>�����l</returns>
		T Start() const { return start_; };
		
		/// <summary>
		/// �ŏI�l�擾
		/// </summary>
		/// <returns>�ŏI�l</returns>
		T End() const { return end_; };

		/// <summary>
		/// �ɋ}�擾
		/// </summary>
		/// <returns>�ɋ}</returns>
		float Exponent() const { return exponent_; }

	private:

		// �����l
		T start_ = T();

		// �ŏI�l
		T end_ = T();

		// �ɋ}(�w��)
		float exponent_ = 0.0f;

	};
}

