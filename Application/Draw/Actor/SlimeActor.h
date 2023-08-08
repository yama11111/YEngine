#pragma once
#include "SplineEase.h"
#include "Timer.h"
#include "Power.h"
#include "Vector3.h"
#include <vector>

namespace YGame
{
	class SlimeActor
	{
	
	public:

		enum class EaseType
		{
			eIn,

			eOut,
		};
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="wobbleScaleValues"> : �g�k�l�x�N�^�[�z��</param>
		/// <param name="frame"> : �t���[��</param>
		/// <param name="exponent"> : �w��</param>
		void Initialize(
			const uint32_t frame, 
			const std::vector<YMath::Vector3>& wobbleScaleValues, 
			const float exponent);

		/// <summary>
		/// �u���u���A�j���[�V����
		/// </summary>
		void Wobble();
		
		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="isSquash"> : �Ԃ�</param>
		void Update(const bool isSquash = false);
	
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
		YMath::Vector3 WobbleScaleValue(const EaseType easeType) const;
	
	public:
		
		virtual ~SlimeActor() = default;
	
	private:
		
		// ����t���O
		bool isAct_ = false;
		
		// �C�[�W���O
		YMath::SplineEase<YMath::Vector3> ease_;
		
		// �^�C�}�[
		YMath::Timer timer_;
		
		// �p���[
		YMath::Power power_;
	};
}

