#pragma once
#include "WorldRuler.h"

namespace YMath
{
	class Timer : private YGame::WorldRuleAdopter
	{
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="end"> : ���� (�I�����̃t���[��)</param>
		/// <param name="isApply"> : ���E�̃X�s�[�h���K�p����邩</param>
		void Initialize(const uint32_t end, const bool isApply = true);
		
		/// <summary>
		/// ���Z�b�g (���g����������)
		/// </summary>
		/// <param name="isAct"> : �������シ����������</param>
		void Reset(const bool isAct);
		
		// �X�V
		void Update();
	
	public:
		
		// �䗦
		float Ratio();
		
		// ���ݎ���
		float Current() const { return count_; }
		
		// �ŏI����
		float End() const { return end_; }
		
		// �����Ă��邩
		bool IsAct() const { return isAct_; }
		
		// �I��������
		bool IsEnd() const { return end_ != 0 && count_ == end_; }
		
	public:
		
		// ����ݒ�
		void SetActive(const bool isAct) { isAct_ = isAct; }

		// �ŏI�l�ݒ�
		void SetEnd(const uint32_t end);

	public:

		Timer() = default;
		
		~Timer() = default;

	private:

		// �J�E���^
		float count_ = 0;

		// �^�C�}�[�I������
		float end_ = 0;

		// ���삵�Ă��邩
		bool isAct_ = false;
	
	};
}