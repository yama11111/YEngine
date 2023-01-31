#pragma once
#include "InputManager.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Model.h"
#include "AudioManager.h"
#include <memory>

namespace YScene
{
	class BaseScene
	{
	public:
		// �ǂݍ���
		virtual void Load() = 0;
		// ������
		virtual void Initialize() = 0;
		// �I������
		virtual void Finalize() = 0;
		// �X�V
		virtual void Update() = 0;
		// �`��
		virtual void Draw() = 0;
	public:
		// �R���X�g���N�^
		BaseScene() = default;
		// �f�X�g���N�^
		virtual ~BaseScene() = default;
	protected:
		// �L�[(�V���O���g��)
		static YInput::Keys* keys_;
		// �}�E�X(�V���O���g��)
		static YInput::Mouse* mouse_;
		// �p�b�h(�V���O���g��)
		static YInput::Pad* pad_;
	protected:
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static YGame::TextureManager* pTexManager_;
		// �ÓI�I�[�f�B�I�}�l�[�W���[�|�C���^
		static YGame::AudioManager* pAudioManager_;
	public:
		// �ÓI������
		static void StaticInitialize(YGame::TextureManager* pTexManager, YGame::AudioManager* pAudioManager);
	};
}
