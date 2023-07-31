#pragma once
#include "UIButton.h"
#include "UILetterBox.h"

namespace YGame
{
	class UIManager final
	{

	public:

		void Initialize();

		void Update();
		
		void StartAnimation();

		void Draw();
	
	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticIntialize();

	public:

		// �W�����v�{�^��
		std::unique_ptr<UIButton> buttonJump_;
		
		// �W�����vUI
		std::unique_ptr<BaseDrawObject> jumpUI_;
		

		// �U���{�^��
		std::unique_ptr<UIButton> buttonAttack_;

		// �U��UI
		std::unique_ptr<BaseDrawObject> attackUI_;
		
		
		// ���^�[�{�b�N�X
		std::unique_ptr<UILetterBox> letterBox_;


		// �J�n�ł��邩
		bool isStartable_ = false;
	};
}

