#pragma once

namespace YGame
{
	class PauseSelection
	{
	
	public:

		// �^�C�g���V�[���p
		enum class TitleScene
		{
			Resume,		// �߂�
			ReStart,	// ���X�^�[�g
			Change,		// �J��
			End, // ���T�C�Y�p
		};

		// �Z���N�g�V�[���p
		enum class SelectScene
		{
			Resume,		// �߂�
			ReStart,	// ���X�^�[�g
			Change,		// �J��
			End, // ���T�C�Y�p
		};

		// �v���C�V�[���p
		enum class PlayScene
		{
			Resume,		// �߂�
			ReStart,	// ���X�^�[�g
			Change,		// �J��
			End, // ���T�C�Y�p
		};
	};
}