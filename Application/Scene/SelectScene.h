#pragma once
#include "BaseScene.h"
#include "DrawObjectForSprite2D.h"
#include "UIButton.h"
#include "UILetterBox.h"
#include "UINumber.h"
#include "Level.h"

namespace YGame
{
	// �Z���N�g�V�[��
	class SelectScene : public BaseScene
	{

	private:

#pragma region ���\�[�X

		Sprite2D* pLogoSpr_ = nullptr;
		
		Sprite2D* pStickSpr_ = nullptr;

		Sprite2D* pButtonSpr_ = nullptr;
		

#pragma endregion

#pragma region �Q�[���I�u�W�F�N�g


		// ���x��
		Level* pLevel_ = nullptr;

		std::unique_ptr<DrawObjectForSprite2D> logoObj_;

		std::unique_ptr<DrawObjectForSprite2D> stickObj_;
		
		std::unique_ptr<DrawObjectForSprite2D> buttonObj_;


		std::unique_ptr<UIButton> startButton_;
		
		// ��
		std::array<Transform, 10> nums_;
		std::array<std::unique_ptr<UINumber>, 10> uiNumbers_;

		uint32_t stageIndex_ = 0;

		// ����
		std::unique_ptr<UILetterBox> letterBox_;

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

