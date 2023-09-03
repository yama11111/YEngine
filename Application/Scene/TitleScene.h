#pragma once
#include "BaseScene.h"

#include "PlayerDrawer.h"
#include "HorseDrawer.h"
#include "MapchipManager.h"

#include "Level.h"

#include "DrawObjectForSprite2D.h"
#include "UIButton.h"
#include "UILetterBox.h"

namespace YGame
{
	// �^�C�g���V�[��
	class TitleScene : public BaseScene
	{

	private:

#pragma region ���\�[�X

		Sprite2D* pLogoSpr_ = nullptr;
		
		Sprite2D* pStartSpr_ = nullptr;
		
		Sprite2D* pButtonSpr_ = nullptr;

#pragma endregion

#pragma region �Q�[���I�u�W�F�N�g

		std::unique_ptr<DrawObjectForSprite2D> logoObj_;

		std::unique_ptr<ConstBufferObject<CBColor>> startColor_;
		std::unique_ptr<DrawObjectForSprite2D> startObj_;
		

		// �v���C���[
		Transform player_;
		std::unique_ptr<PlayerDrawer> playerDra_;
		
		// �E�}
		Transform horse_;
		std::unique_ptr<HorseDrawer> horseDra_;

		// ���x��
		Level* pLevel_ = nullptr;

		// �}�b�v�`�b�v�}�l�[�W���[
		MapChipManager* pMapChipManager_ = nullptr;


		// �X�^�[�g�{�^��
		std::unique_ptr<UIButton> startButton_;

		// ����
		std::unique_ptr<UILetterBox> letterBox_;

		// �]���p�r���[�v���W�F�N�V����
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
		TitleScene() = default;
		
		// �f�X�g���N�^
		~TitleScene() = default;
	};
}
