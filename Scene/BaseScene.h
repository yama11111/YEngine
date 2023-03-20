#pragma once
#include "InputManager.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Model.h"
#include "AudioManager.h"
#include "WorldRuler.h"
#include <memory>

namespace YScene
{
	// ���V�[���N���X
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
		static YInput::Keys* sKeys_;
		// �}�E�X(�V���O���g��)
		static YInput::Mouse* sMouse_;
		// �p�b�h(�V���O���g��)
		static YInput::Pad* sPad_;
	protected:
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^(�V���O���g��)
		static YGame::TextureManager* spTexManager_;
		// �ÓI�I�[�f�B�I�}�l�[�W���[�|�C���^(�V���O���g��)
		static YGame::AudioManager* spAudioManager_;
		// �ÓI�Q�[�����[���|�C���^
		static YGame::WorldRuler* spWorldRuler_;
	public:
		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pWorldRuler"> : �Q�[�����[���|�C���^</param>
		static void StaticInitialize(YGame::WorldRuler* pWorldRuler);
	};
}
