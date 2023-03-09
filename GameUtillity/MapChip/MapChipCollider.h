#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace YGame
{
	class MapChipCollider
	{
	private:
		YMath::Vector3 scale_; // �傫��
		bool isLanding_ = false; // �n��ɂ��邩 
		bool isElderLanding_ = false; // �n��ɂ����� 
	public:
		struct InitStatus
		{
			YMath::Vector3 scale_; // �傫��
		};
	public:
		// �}�b�v�Փːݒ菉����
		void Initialize(const InitStatus& state);
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
		// �n��ɂ��邩�ݒ�
		void SetIsLanding(const bool isLanding) { isLanding_ = isLanding; }
		// �n��ɂ������ݒ�
		void SetIsElderLanding(const bool isElderLanding) { isElderLanding_ = isElderLanding; }
	};
}
