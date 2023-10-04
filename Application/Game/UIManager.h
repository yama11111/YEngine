#pragma once
#include "UIButton.h"
#include "UILetterBox.h"

namespace YGame
{
	class UIManager final
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		
		/// <summary>
		/// �J�n�A�j���[�V����
		/// </summary>
		void PlayStartAnimation();

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();
	
	public:

		/// <summary>
		/// �ǂݍ���
		/// </summary>
		static void LoadResource();

	private:
		
		// ���^�[�{�b�N�X
		std::unique_ptr<UILetterBox> letterBox_;


		// �W�����v�{�^��
		std::unique_ptr<UIButton> buttonJump_;
		
		// �W�����vUI
		std::unique_ptr<BaseDrawObject> jumpUI_;
		

		// �U���{�^��
		std::unique_ptr<UIButton> buttonAttack_;

		// �U��UI
		std::unique_ptr<BaseDrawObject> attackUI_;
		
	};
}

