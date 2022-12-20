#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "Sprite.h"
#include "Model.h"
#include "Billboard.h"
#include "AudioManager.h"
#include "CollisionManager.h"
#include <memory>

#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include "MapChipManager.h"
#include "CameraManager.h"
#include "SceneManager.h"

namespace Game
{
	class GameScene
	{
	public:
#pragma region ���\�[�X

		// ----- �e�N�X�`�� ----- //
		
		// ���n�摜
		UINT plainT_ = 0;
		// �v���C���[�摜
		UINT playerT_ = 0;
		// �G�l�~�[�摜
		UINT enemyT_ = 0;
		// �}�b�v2D�\���p�摜
		UINT mapDispT_ = 0;

		// ----- �I�[�f�B�I ----- //

		//UINT aA_ = 0;

		// ----- �X�v���C�g ----- //
		
		// ��ʑS��
		std::unique_ptr<Sprite> curtenS_ = nullptr;
		// �}�b�v2D�\���p
		std::unique_ptr<Sprite> mapDispS_ = nullptr;

		// ----- ���f�� ----- //
		
		// �����̃��f��
		std::unique_ptr<Model> cubeM_ = nullptr;
		// �V�����f��
		std::unique_ptr<Model> skydomeM_ = nullptr;

		// ----- �r���{�[�h ----- //

		std::unique_ptr<Billboard> aB_ = nullptr;


#pragma endregion
#pragma region �Q�[���I�u�W�F�N�g

		// ��
		std::vector<std::vector<Object>> floor;

		// �v���C���[
		std::unique_ptr<Player> player_ = nullptr;

		// �G�l�~�[
		Object enemy_;

		Object billboard_;

		// �}�b�v
		MapChip map_;

		// �V��
		Skydome skydome_;

		// �J�����}�l�[�W���[
		CameraManager cameraMan_;
		Camera camera_;

		// �]���p�r���[�v���W�F�N�V����
		ViewProjection vp_;

		// �A�^������}�l�[�W���[
		Collision::CollisionManager collMan_;

		// �V�[���}�l�[�W���[
		SceneManager sceneMan_;

#pragma endregion
	public:
		// �ǂݍ���
		void Load();
		// ������
		void Initialize();
		// �X�V
		void Update();
		// �`��
		void Draw();
	private:
		// �w�i�X�v���C�g�`��
		void DrawBackSprites();
		// ���f���`��
		void DrawModels();
		// �r���{�[�h�`��
		void DrawBillboards();
		// �O�i�X�v���C�g�`��
		void DrawFrontSprites();
	public:
		// �R���X�g���N�^
		GameScene();
		// �f�X�g���N�^
		~GameScene();
	private:
		// �L�[(�V���O���g��)
		static YInput::Keys* keys_;
		// �}�E�X(�V���O���g��)
		static YInput::Mouse* mouse_;
		// �p�b�h(�V���O���g��)
		static YInput::Pad* pad_;
	private:
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static TextureManager* pTexManager_;
		// �ÓI�I�[�f�B�I�}�l�[�W���[�|�C���^
		static AudioManager* pAudioManager_;
	public:
		// �ÓI������
		static void StaticInitialize(TextureManager* pTexManager, AudioManager* pAudioManager);
	};
}