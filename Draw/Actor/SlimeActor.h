#pragma once
#include "Lerp.h"
#include "Timer.h"
#include <vector>

namespace YGame
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
		// �h��X�e�[�^�X
		struct JiggleState
		{
			YMath::Vector3 value_;
			unsigned int frame_;
			float exponent_ = 2.0f;
		};
	private:
		// �����Ă��邩�t���O
		bool isAct_ = false;
		// ���݂̓���
		Action action_ = Action::None;
		// �C�[�W���O
		YMath::Ease<YMath::Vector3> ease_;
		// �I���l
		std::vector<JiggleState> jiggles_;
		// ���݂̃C���f�b�N�X
		size_t currentIdx_ = 0;
		// �^�C�}�[
		YMath::Timer timer_;
		// ���l
		YMath::Vector3 value_;
	public:
		// ������
		void Initialize();
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="jiggles"> : �h��X�e�[�^�X</param>
		/// <param name="---------------------------"></param>
		/// <param name="(Vector3) jiggles.value_"> : �h����</param>
		/// <param name="(uint) jiggles.frame_"> : �t���[��</param>
		/// <param name="(float) jiggles.exponent_"> : �w��</param>
		void Activate(const std::vector<JiggleState>& jiggles);
		// �X�V
		void Update();
	public:
		// ���l�擾
		YMath::Vector3 JiggleValue();
	private:
		// �����؂�ւ�
		void ChangeAction();
		// ���l�X�V
		void UpdateValue();
	public:
		virtual ~SlimeActor() = default;
	};
}

