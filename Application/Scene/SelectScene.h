#pragma once
#include "BaseScene.h"
#include "DrawObjectForSprite2D.h"
#include "UIButton.h"
#include "UIDigit.h"
#include "UINumber.h"

namespace YGame
{
	// �Z���N�g�V�[��
	class SelectScene : public BaseScene
	{

	private:

#pragma region ���\�[�X

		Sprite2D* pLogoSpr_ = nullptr;

		Sprite2D* pStartSpr_ = nullptr;
		
		Sprite2D* pNumberSpr_ = nullptr;
		
		Sprite2D* pStickSpr_ = nullptr;

		Sprite2D* pButtonSpr_ = nullptr;
		

#pragma endregion

#pragma region �Q�[���I�u�W�F�N�g

		std::unique_ptr<DrawObjectForSprite2D> logoObj_;

		std::unique_ptr<DrawObjectForSprite2D> startObj_;

		std::unique_ptr<DrawObjectForSprite2D> numberObj_;
		
		std::unique_ptr<DrawObjectForSprite2D> stickObj_;
		
		std::unique_ptr<DrawObjectForSprite2D> buttonObj_;


		std::unique_ptr<UIButton> startButton_;
		
		Transform num;
		std::unique_ptr<UIDigit> uiDigit_;
		std::unique_ptr<UINumber> uiNumber_;

		// �r���[�v���W�F�N�V����
		YGame::ViewProjection transferVP_;

#pragma endregion

	public:

		/// <summary>
		/// �ǂݍ���
		/// </summary>
		void Load() override;

		/// <summary>
		/// ������
		/// </summary>
		void Initialize() override;

		/// <summary>
		/// �I������
		/// </summary>
		void Finalize() override;

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

	public:
		
		// �R���X�g���N�^
		SelectScene() = default;
		
		// �f�X�g���N�^
		~SelectScene() = default;

	};
}

