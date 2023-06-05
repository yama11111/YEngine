#pragma once
#include "WorldRuler.h"

namespace YMath
{
	class Power : private YGame::WorldRuleAdopter
	{
	private:
		// �J�E���^
		float count_ = 0;
		// �p���[�ő厞
		float max_ = 0;
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="max"> : �� (�ő厞�̃p���[)</param>
		/// <param name="isApply"> : ���E�̃X�s�[�h���K�p����邩</param>
		void Initialize(const unsigned int max, const bool isApply = true);
		// ���Z�b�g
		void Reset();
		// �X�V
		void Update(const bool isAct);
	public:
		// �䗦
		float Ratio();
		// ���݃p���[
		float Current() const { return count_; }
		// �ő�p���[
		float Max() const { return max_; }
		// �ő傩
		bool IsMax() const { return count_ == max_; }
		// �[����
		bool IsZero() const { return count_ == 0; }
	};
}