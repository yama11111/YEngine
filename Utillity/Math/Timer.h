#pragma once
#include "WorldRuler.h"

namespace YMath
{
	class Timer : private YGame::WorldRuleAdopter
	{
	private:
		// �J�E���^
		float count_ = 0;
		// �^�C�}�[�I������
		float end_ = 0;
		// ���삵�Ă��邩
		bool isAct_ = false;
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="end"> : ���� (�I�����̃t���[��)</param>
		/// <param name="isApply"> : ���E�̃X�s�[�h���K�p����邩</param>
		void Initialize(const unsigned int end, const bool isApply = true);
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
		float Current() { return count_; }
		// �����Ă��邩
		bool IsAct() { return isAct_; }
		// �I��������
		bool IsEnd() { return end_ != 0 && count_ == end_; }
		// ����ݒ�
		void SetActive(bool isAct) { isAct_ = isAct; }
	};
}