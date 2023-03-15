#pragma once
#include "Lerp.h"

namespace YGame
{
	// �Q�[�����[�� (�V���O���g��)
	class WorldRuler
	{
	private:
		// ���ԃX�s�[�h
		float timeSpd_ = 1.0f;
		// �d��
		float gravity_ = 0.3f;
		// ���C
		float friction_ = 0.5f;

		// �C���t���O
		bool isModify_ = false;
		
		// �J�E���g
		unsigned int modifyCount_ = 0;
		// �C������
		unsigned int modifyFrame_ = 0;

		// ���ԃX�s�[�h��ԃN���X
		YMath::Ease<float> timeSpdEas_;
		// �d�͕�ԃN���X
		YMath::Ease<float> gravityEas_;
		// ���C��ԃN���X
		YMath::Ease<float> frictionEas_;
	public:
		// ������
		void Initailze();
		// ���Z�b�g
		void Reset();
		// �X�V
		void Update();
	public:
		/// <summary>
		/// �C��
		/// </summary>
		/// <param name="time"> : ���� (�����鎞��)</param>
		/// <param name="exponent"> : �w�� (�ɋ})</param>
		void Modify(const unsigned int time, const float exponent = 2.0f);
		
		// ���ԃX�s�[�h�擾
		float GetTimeSpeed() const { return timeSpd_; }
		// ���ԃX�s�[�h�ݒ�
		void SetTimeSpeed(const float timeSpd);

		// �d�͎擾
		float GetGravity() const {return gravity_;}
		// �d�͐ݒ�
		void SetGravity(const float gravity);

		// ���C�擾
		float GetFriction() const {return friction_;}
		// ���C�ݒ�
		void SetFriction(const float friction);
	};

	class WorldRuleAdopter
	{
	protected:
		// �K�p���邩
		bool isApply_ = true;
	protected:
		// �ÓI�Q�[�����[���|�C���^
		static WorldRuler* spWorldRuler_;
	public:
		// �ÓI������
		static void StaticInitialize(WorldRuler* pWorldRuler);
	};
}

