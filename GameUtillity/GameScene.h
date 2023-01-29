#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "Sprite2D.h"
#include "Model.h"
#include "Sprite3D.h"
#include "AudioManager.h"
#include "CollisionManager.h"
#include <memory>

#include "Floor.h"
#include "Player.h"
#include "PlayerDrawer.h"
#include "EnemyManager.h"
#include "Skydome.h"
#include "MapChipManager.h"
#include "CameraManager.h"
#include "SceneManager.h"

namespace YGame
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
		// �}�b�v�摜
		UINT mapT_ = 0;
		// �}�b�v2D�\���p�摜
		UINT mapDispT_ = 0;

		// ----- �I�[�f�B�I ----- //

		//UINT aA_ = 0;

		// ----- �X�v���C�g ----- //
		
		// ��ʑS��
		std::unique_ptr<Sprite2D> windowS_ = nullptr;
		// �V�[���J�ڗp
		std::unique_ptr<Sprite2D> curtenS_ = nullptr;
		// �}�b�v2D�\���p
		std::unique_ptr<Sprite2D> mapDispS_ = nullptr;

		// ----- ���f�� ----- //
		
		// �����̃��f��
		std::unique_ptr<Model> cubeM_ = nullptr;
		// �V�����f��
		std::unique_ptr<Model> skydomeM_ = nullptr;
		// �X���C�����f��
		std::unique_ptr<Model> slimeM_ = nullptr;

		// ���񂾂��񃂃f��
		std::unique_ptr<Model> zundamonM_ = nullptr;

		// ----- �r���{�[�h ----- //


#pragma endregion
#pragma region �Q�[���I�u�W�F�N�g

		// �v���C���[
		ObjectModel player_;
		YDrawer::PlayerDrawer playerDra_;

		// �}�b�v�}�l�[�W���[
		MapChipManager mapMan_;

		// �p�[�e�B�N���}�l�[�W���[
		YParticle::ParticleManager particleMan_;

		// �V��
		Skydome skydome_;

		// �J�����}�l�[�W���[
		YCamera::CameraManager cameraMan_;

		// �]���p�r���[�v���W�F�N�V����
		ViewProjection vp_;

		// �A�^������}�l�[�W���[
		YCollision::CollisionManager collMan_;

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
		void DrawBackSprite2Ds();
		// ���f���`��
		void DrawModels();
		// �r���{�[�h�`��
		void DrawSprite3Ds();
		// �O�i�X�v���C�g�`��
		void DrawFrontSprite2Ds();
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
