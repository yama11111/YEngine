#pragma once

namespace CharaConfig 
{
	// �d��
	const float GravityPower = 0.3f;

	// �v���C���[
	namespace Player 
	{
		// ���a (�A�^������)
		const float CollRad = 10.0f;
		
		// �̗�
		const int HP = 2;

		// ���G����
		const int CheatTime = 20;

		// �ő�W�����v��
		const int MaxJumpCount = 2;

		// �W�����v��
		const float RisePower = 4.5f;
	}

	// �G�l�~�[
	namespace Enemy
	{
		// ���G����
		const int CheatTime = 0;

		// �X���C��
		namespace Slime
		{
			// ���a (�A�^������)
			const float CollRad = 10.0f;

			// �̗�
			const int HP = 1;
		}
	}
}