#pragma once
#include "BaseScene.h"
#include "MapChipManager.h"
#include "CharacterManager.h"
#include "PauseManager.h"
#include "ScrollCamera.h"
#include "UIManager.h"

#include "Level.h"

namespace YGame
{
	// �Q�[���V�[��
	class PlayScene : public BaseScene
	{

	public:

#pragma region ���\�[�X


#pragma endregion

#pragma region �Q�[���I�u�W�F�N�g

		// ���x��
		Level* pLevel_ = nullptr;

		// �L�����N�^�[�}�l�[�W���[
		CharacterManager* pCharacterMan_ = nullptr;

		// �}�b�v�`�b�v�}�l�[�W���[
		MapChipManager* pMapChipManager_ = nullptr;

		// �X�N���[���J����
		ScrollCamera scrollCamera_;

		// �]���p�r���[�v���W�F�N�V����
		ViewProjection transferVP_;

		// UI�}�l�[�W���[
		UIManager uiMan_;
		
		// �J�n�t���O
		bool isStart_ = false;

		// �J�n���o�p�^�C�}�[
		YMath::Timer startTimer_;

		// �J�n���o�p�J�����I�t�Z�b�g
		YMath::Ease<YMath::Vector3> cameraOffset_;
		
		// ��~�t���O
		bool isStop_ = false;

		PauseManager pause_;

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
		PlayScene() = default;

		// �f�X�g���N�^
		~PlayScene() = default;

	};
}
