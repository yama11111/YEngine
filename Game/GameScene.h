#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "Sprite.h"
#include "Model.h"
#include "AudioManager.h"
#include <memory>

#include "Skydome.h"
#include "SceneManager.h"
#include "CameraManager.h"

namespace Game
{
	class GameScene
	{
	public:
		// ----- �e�N�X�`�� ----- //
		
		// ���n�摜
		UINT plainT_ = 0;
		// �v���C���[�摜
		UINT playerT_ = 0;
		// �G�l�~�[�摜
		UINT enemyT_ = 0;

		// ----- �I�[�f�B�I ----- //

		// 
		UINT aA_ = 0;

		// ----- ���f�� ----- //
		
		// �����̃��f��
		std::unique_ptr<Model> cubeM_ = nullptr;
		// �V�����f��
		std::unique_ptr<Model> skydomeM_ = nullptr;

		// ----- �X�v���C�g ----- //
		
		// sprite
		std::unique_ptr<Sprite> quadS_ = nullptr;
		// 
		std::unique_ptr<Sprite> curtenS_ = nullptr;

		// ----- �I�u�W�F�N�g ----- //
		
		// ��
		std::vector<std::vector<Object>> floor;

		// 
		Object sprite_;
		Object player_;
		Object enemy_;

		Skydome skydome_;

		// �]���p�r���[�v���W�F�N�V����
		ViewProjection vp_;

		// �V�[���}�l�[�W���[
		SceneManager sceneMan_;
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
		// �O�i�X�v���C�g�`��
		void DrawFrontSprites();
	public:
		// �R���X�g���N�^
		GameScene();
		// �f�X�g���N�^
		~GameScene();
	private:
		// �L�[(�V���O���g��)
		static Input::Keys* keys_;
		// �}�E�X(�V���O���g��)
		static Input::Mouse* mouse_;
		// �p�b�h(�V���O���g��)
		static Input::Pad* pad_;
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
