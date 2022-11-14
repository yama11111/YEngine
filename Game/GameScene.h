#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "Sprite.h"
#include "Model.h"
#include "AudioManager.h"
#include <memory>

#include "PlayerDrawer.h"
#include "EnemyDrawer.h"

namespace Game
{
	class GameScene
	{
	public:
		// ----- ���\�[�X ----- //

		// ���n�摜
		UINT plainT_ = 0;

		UINT aA_ = 0;

		// model
		std::unique_ptr<Model> cubeM_ = nullptr;

		// sprite
		std::unique_ptr<Sprite> quadS_ = nullptr;

		// ----- �I�u�W�F�N�g ----- //
		std::vector<std::vector<Transform>> floor;

		// Transform
		Transform player_;
		Transform enemy_;

		// drawer
		PlayerDrawer pd_;
		EnemyDrawer ed_;

		// �]���p�r���[�v���W�F�N�V����
		ViewProjection vp_;
	public:
		// ������
		void Initialize();
		// �X�V
		void Update();
		// �`��
		void Draw();
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
