#pragma once

namespace Math
{
	class Timer
	{
	private:
		// �J�E���^
		unsigned int count_ = 0;
		// �^�C�}�[�I������
		unsigned int t_ = 0;
		// ���삵�Ă��邩
		bool isAct_ = false;
	public:
		// ������
		void Initialize(const unsigned int time);
		// ���Z�b�g
		void Reset(const bool isAct);
		// �X�V
		void Update();
	public:
		// �䗦
		float Ratio();
		// ���ݎ���
		unsigned int Current() { return count_; }
		// �����Ă��邩
		bool IsAct() { return isAct_; }
		// �I��������
		bool IsEnd() { return t_ != 0 && count_ == t_; }
		// ����ݒ�
		void SetActive(bool isAct) { isAct_ = isAct; }
	};
}