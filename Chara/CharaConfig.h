#pragma once
#include "Vec4.h"

namespace CharaConfig 
{
	// �d��
	const float GravityPower = 0.3f;

	// �U���͈�
	const float AttackRange = 2.0f;

	// �v���C���[
	namespace Player 
	{
		// ���a (�A�^������)
		const float CollRad = 4.5f;
		
		// �̗�
		const int HP = 100;

		// ���G����
		const int CheatTime = 20;

		// �ő�W�����v��
		const int MaxJumpCount = 2;

		// �W�����v��
		const float RisePower = 6.0f;
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
			const float CollRad = 4.5f;

			// �̗�
			const int HP = 100;
		}
	}

	// �X���C���A�j���[�V����
	namespace SlimeAct
	{
		// �u���u������
		const int Frame = 4;

		// �L�k��
		const float ElasticityValue = 0.5f;

		// �Ԃ��� (���n��)
		const float SquashValue = 0.75f;
	}

	// �q�b�g�A�j���[�V����
	namespace HitAct
	{
		// �U����
		const float ShakeValue = 3.0f;

		// �F
		const YMath::Vec4 Color = { 1.0f, 0.25f, 0.25f, 1.0f };

		// ���ߗ�
		const float AlphaValue = 0.5f;
	}
}