#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace YGame
{
	class MapChipCollider
	{

	protected:

		/// <summary>
		/// �}�b�v�Փːݒ菉����
		/// </summary>
		/// <param name="scale"> : �傫��</param>
		void Initialize(const  YMath::Vector3& scale);
	
	public:
		
		// �ʒu�擾 (�Q��)
		virtual YMath::Vector3& PosRef() = 0;
		
		// �傫���擾
		YMath::Vector3 Scale() const { return scale_; }
		
		// �X�s�[�h�擾 (�Q��)
		virtual YMath::Vector3& SpeedRef() = 0;
		
		// �n��ɂ��邩
		bool IsLanding() const { return isLanding_; }
		
		// �n��ɂ�����
		bool IsElderLanding() const { return isElderLanding_; }
		
	public:

		// �n��ɂ��邩�ݒ�
		void SetIsLanding(const bool isLanding) { isLanding_ = isLanding; }
		
		// �n��ɂ������ݒ�
		void SetIsElderLanding(const bool isElderLanding) { isElderLanding_ = isElderLanding; }
	
	private:
		
		// �傫��
		YMath::Vector3 scale_;
		
		// �n��ɂ��邩 
		bool isLanding_ = false;
		
		// �n��ɂ����� 
		bool isElderLanding_ = false;
	
	};
}
