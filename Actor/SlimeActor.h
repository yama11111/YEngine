#pragma once
#include "Lerp.h"
#include "Timer.h"
#include <vector>

namespace YActor
{
	class SlimeActor
	{
	private:
		// ����
		enum class  Action
		{
			None,		 // ����
			Elasticity,	 // �L�яk��
			Normal,		 // �ʏ�
		};
	private:
		// �����Ă��邩�t���O
		bool isAct_ = false;
		// ���݂̓���
		Action action_ = Action::None;
		// �C�[�W���O
		YMath::Ease<YMath::Vec3> ease_;
		// �I���l
		std::vector<YMath::Vec3> ends_;
		// ���݂̃C���f�b�N�X
		size_t currentIdx_ = 0;
		// �^�C�}�[
		YMath::Timer timer_;
		// ���l
		YMath::Vec3 value_;
	public:
		// ������
		void InitializeSlimeAct();
		// ������
		void ActivateSlimeAct(const std::vector<YMath::Vec3> ends, const unsigned int frame);
		// �X�V
		void UpdateSlimeAct();
		// ���l�擾
		YMath::Vec3 SlimeActValue();
	private:
		// �����؂�ւ�
		void ChangeAction();
		// ���l�X�V
		void UpdateValue();
	};
}

