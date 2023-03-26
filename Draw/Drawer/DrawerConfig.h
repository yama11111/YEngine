#pragma once

// �`��p�N���X
namespace DrawerConfig
{
	// �v���C���[
	namespace Player 
	{
		// �������[�V����
		namespace Idle
		{
			// �Ԋu
			const unsigned int IntervalTime = 10;

			// �Ղ�Ղ�A�j���[�V����
			namespace SlimeAction
			{
				// �L�k��
				const float Value = 0.5f;

				// ���� (F)
				const unsigned int Frame = 20;

				// �w��
				const float Power = 3.0f;
			}
		}

		// �W�����v���[�V����
		namespace Jump
		{
			// �Ղ�Ղ�A�j���[�V����
			namespace SlimeAction
			{
				// �L�k��
				const float Value = 0.5f;

				// ���� (F)
				const unsigned int Frame = 20;

				// �w��
				const float Power = 3.0f;
			}
		}

		// ���n���[�V����
		namespace Landing
		{
			// �Ղ�Ղ�A�j���[�V����
			namespace SlimeAction
			{
				// �L�k��
				const float Value = 0.5f;
				
				// ���� (F)
				const unsigned int Frame = 20;

				// �w��
				const float Power = 3.0f;
			}
		}
	}

	// �t�B���^�[
	namespace Filter 
	{
		// �������[�V����
		namespace Idle
		{
			// �Ԋu
			const unsigned int IntervalTime = 10;
		}
	}

	// �u���b�N
	namespace Block
	{
		// �������[�V����
		namespace Idle
		{
			// �Ԋu
			const unsigned int IntervalTime = 10;
		}
	}

	// �Q�[�g
	namespace Gate
	{
		// �������[�V����
		namespace Idle
		{
			// �Ԋu
			const unsigned int IntervalTime = 10;
		}
	}

	// �S�[��
	namespace Goal
	{
		// �������[�V����
		namespace Idle
		{
			// �Ԋu
			const unsigned int IntervalTime = 10;
		}
	}
}