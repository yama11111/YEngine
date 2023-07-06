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
		void Reset(const bool isAct);
		
		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
	
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
		inline float EndFrame() const { return endFrame_; }

		/// <summary>
		/// �����Ă��邩
		/// </summary>
		inline bool IsAct() const { return isAct_; }

		/// <summary>
		/// �I��������
		/// </summary>
		inline bool IsEnd() const { return endFrame_ != 0 && current_ == endFrame_; }

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
		void SetEndFrame(const uint32_t endFrame);

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
		float endFrame_ = 0;
	};
}