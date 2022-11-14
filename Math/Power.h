#pragma once

namespace Math
{
	class Power
	{
	private:
		// �J�E���^
		int count_ = 0;
		// �p���[�ő厞
		int p_ = 0;
		// ���삵�Ă��邩
		bool isAct_ = false;
	public:
		// ������
		void Initialize(const unsigned int max);
		// ���Z�b�g
		void Reset();
		// �X�V
		void Update(const bool isAct);
	public:
		// �䗦
		float Ratio();
		// ���݃p���[
		unsigned int Current() { return count_; }
		// �����Ă��邩
		bool IsAct() { return isAct_; }
		// �ő傩
		bool IsMax() { return count_ == p_; }
		// �[����
		bool IsZero() { return count_ == 0; }
	};
}