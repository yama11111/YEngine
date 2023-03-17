#pragma once
#include "Vector4.h"

namespace CharaConfig 
{
	// �v���C���[
	namespace Player 
	{
		// ���a (�A�^������)
		const float CollRad = 4.5f;
		// �̗�
		const int HP = 1;
		// ���G����
		const int CheatTime = 20;

		// �ő�W�����v��
		const int MaxJumpCount = 1;
		// �W�����v��
		const float RisePower = 6.0f;

		// �������[�V�����Ԋu�t���[��
		const int IdleIntervalFrame = 20;
	}

	// �G�l�~�[
	namespace Enemy
	{
		// ���G����
		const int CheatTime = 5;

		// �X���C��
		namespace Slime
		{
			// ���a (�A�^������)
			const float CollRad = 8.0f;

			// �̗�
			const int HP = 1;
		}
	}

	// �X���C���A�j���[�V����
	namespace SlimeAct
	{
		// �u���u������
		const unsigned int Frame = 4;
		// �p���[
		const float Power = 2.0f;
		// �L�k��
		const float ElasticityValue = 0.1f;
		// �Ԃ��� (���n��)
		const float SquashValue = 0.25f;
	}

	// �q�b�g�A�j���[�V����
	namespace HitAct
	{
		// �U����
		const float ShakeValue = 3.0f;

		// �F
		const YMath::Vector4 Color = { 1.0f, 0.0f, 0.0f, 1.0f };

		// ���ߗ�
		const float AlphaValue = 0.5f;
	}
}