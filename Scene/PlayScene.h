#pragma once
#include "BaseScene.h"

namespace YScene
{
	// �Q�[���V�[��
	class PlayScene : public BaseScene
	{
	public:
#pragma region ���\�[�X

		// ----- �e�N�X�`�� ----- //
		
		// ���n�摜
		UINT plainTex_ = 0;

		// ----- �I�[�f�B�I ----- //

		// ----- �X�v���C�g (2D) ----- //
		
		// ��ʑS��
		std::unique_ptr<YGame::Sprite2D> windowSpr_ = nullptr;
		
		// ----- �X�v���C�g (3D) ----- //

		// ----- ���f�� ----- //
		
		// �����̃��f��
		std::unique_ptr<YGame::Model> cubeMod_ = nullptr;

#pragma endregion
#pragma region �Q�[���I�u�W�F�N�g


		// �]���p���C�g�O���[�v
		std::unique_ptr<YGame::LightGroup> lightGroup_;

		// �]���p�r���[�v���W�F�N�V����
		YGame::ViewProjection vp_;

#pragma endregion
	public:
		// �ǂݍ���
		void Load() override;
		// ������
		void Initialize() override;
		// �I������
		void Finalize() override;
		// �X�V
		void Update() override;
		// �`��
		void Draw() override;
	private:
		// �w�i�X�v���C�g2D�`��
		void DrawBackSprite2Ds();
		// �X�v���C�g3D�`��
		void DrawBackSprite3Ds();
		// ���f���`��
		void DrawModels();
		// �X�v���C�g3D�`��
		void DrawFrontSprite3Ds();
		// �O�i�X�v���C�g2D�`��
		void DrawFrontSprite2Ds();
	public:
		// �R���X�g���N�^
		PlayScene() = default;
		// �f�X�g���N�^
		~PlayScene() = default;
	};
}
