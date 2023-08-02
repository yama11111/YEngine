#pragma once
#include "Ease.h"
#include "Timer.h"
#include "Vector3.h"
#include <vector>

namespace YGame
{
	class SlimeActor
	{
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// �u���u���A�j���[�V����
		/// </summary>
		/// <param name="wobbleScaleValues"> : �g�k�l�x�N�^�[�z��</param>
		/// <param name="frame">"> : �t���[��</param>
		/// <param name="exponent">"> : �w��</param>
		void Wobble(const std::vector<YMath::Vector3>& wobbleScaleValues, const uint32_t frame, const float exponent);
		
		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
	
	public:
	
		/// <summary>
		/// ���쒆��
		/// </summary>
		/// <returns>����t���O</returns>
		inline bool IsAct() const { return isAct_; }

		/// <summary>
		/// ���݂̊g�k�l�擾
		/// </summary>
		/// <returns>���݂̊g�k�l</returns>
		inline YMath::Vector3 WobbleScaleValue() const { return value_; }
	
	public:
		
		virtual ~SlimeActor() = default;
	
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
		YMath::Ease<YMath::Vector3> ease_;
		
		// �I���l
		std::vector<YMath::Vector3> wobbleScaleValues_;

		// �w��
		float exponent_ = 0.0f;
		
		// ���݂̃C���f�b�N�X
		size_t currentIdx_ = 0;
		
		// �^�C�}�[
		YMath::Timer timer_;
		
		// ���l
		YMath::Vector3 value_;
	
	private:
		
		/// <summary>
		/// �����؂�ւ�
		/// </summary>
		void ChangeAction();
		
		/// <summary>
		/// ���l�X�V
		/// </summary>
		void UpdateValue();
	
	};
}

