#pragma once
#include "PauseDrawer.h"

namespace YGame
{
	class PauseManager final
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// ���Z�b�g
		/// </summary>
		void Reset();

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

	public:

		/// <summary>
		/// �|�[�Y����
		/// </summary>
		/// <returns>�|�[�Y����</returns>
		bool IsPause() const { return isPause_; }

		/// <summary>
		/// �|�[�Y����������
		/// </summary>
		/// <returns>�|�[�Y����</returns>
		bool IsElderPause() const { return isElderPause_; }

	private:

		void ChangeSelect();

		void ResumeReset();

	private:

		// �|�[�Y����
		bool isPause_ = false;

		// �|�[�Y����������
		bool isElderPause_ = false;

		// ���݂̑I��
		PauseDrawer::Selection current_ = PauseDrawer::Selection::Resume;
	
		// �`��N���X
		PauseDrawer pauseDra_;

	};
}
