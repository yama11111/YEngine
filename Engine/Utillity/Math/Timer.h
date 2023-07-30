#pragma once
#include <cstdint>

namespace YMath
{
	class Timer
	{
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="endFrame"> : �I�����̎��� (F)</param>
		/// <param name="isAct"> : �������シ����������</param>
		void Initialize(const uint32_t endFrame, const bool isAct = false);
		
		/// <summary>
		/// ���Z�b�g (���g����������)
		/// </summary>
		/// <param name="isAct"> : �������シ����������</param>
		void Reset(const bool isAct = false);
		
		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="passRate"> : ���Ԃ̌o�ߗ�</param>
		void Update(const float passRate = 1.0f);
	
	public:
		
		/// <summary>
		/// �䗦
		/// </summary>
		float Ratio();

		/// <summary>
		/// ���ݎ���
		/// </summary>
		inline float Current() const { return current_; }

		/// <summary>
		/// �ŏI����
		/// </summary>
		inline uint32_t EndFrame() const { return endFrame_; }

		/// <summary>
		/// �����Ă��邩
		/// </summary>
		inline bool IsAct() const { return isAct_; }

		/// <summary>
		/// �I��������
		/// </summary>
		inline bool IsEnd() const { return endFrame_ != 0 && current_ == static_cast<float>(endFrame_); }

	public:
		
		/// <summary>
		/// ����ݒ�
		/// </summary>
		/// <param name="isAct"> : ��������</param>
		inline void SetActive(const bool isAct) { isAct_ = isAct; }

		/// <summary>
		/// �I�������ݒ�
		/// </summary>
		/// <param name="end"> : �I������ (F)</param>
		inline void SetEndFrame(const uint32_t endFrame) { endFrame_ = endFrame; }

	public:

		Timer() = default;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="endFrame"> : �I�����̎��� (F)</param>
		/// <param name="isAct"> : �������シ����������</param>
		Timer(const uint32_t endFrame, const bool isAct = false);
		
		~Timer() = default;

	private:

		// ���삵�Ă��邩
		bool isAct_ = false;

		// ���ݎ���
		float current_ = 0;

		// �^�C�}�[�I������
		uint32_t endFrame_ = 0;
	};
}