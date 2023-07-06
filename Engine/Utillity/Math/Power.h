#pragma once
#include <cstdint>

namespace YMath
{
	class Power
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="maxPower"> : �ő�p���[</param>
		void Initialize(const uint32_t maxPower);

		/// <summary>
		/// ���Z�b�g (���g����������)
		/// </summary>
		void Reset();

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="isAct"> : ���삷�邩 (���쒆���Z)</param>
		void Update(const bool isAct);

	public:

		/// <summary>
		/// �䗦
		/// </summary>
		float Ratio();

		/// <summary>
		/// ���݃p���[
		/// </summary>
		inline float Current() const { return current_; }

		/// <summary>
		/// �ő�p���[
		/// </summary>
		inline float Max() const { return maxPower_; }

		/// <summary>
		/// �ő傩
		/// </summary>
		inline bool IsMax() const { return current_ == maxPower_; }

		/// <summary>
		/// �[����
		/// </summary>
		inline bool IsZero() const { return current_ == 0; }

	public:

		/// <summary>
		/// �ŏI�l�ݒ�
		/// </summary>
		/// <param name="max"></param>
		void SetMaxPower(const uint32_t max);

	public:

		Power() = default;

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="maxPower"> : �ő�p���[</param>
		Power(const uint32_t maxPower);
		
		~Power() = default;
	
	private:
		
		// ���݃p���[
		float current_ = 0;
		
		// �ő厞�p���[
		float maxPower_ = 0;
	};
}