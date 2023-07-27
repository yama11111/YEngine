#pragma once
#include "BaseScene.h"
#include "MapChipManager.h"
#include "CharacterManager.h"
#include "ScrollCamera.h"

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
		Level* pLevel_;

		// �L�����N�^�[�}�l�[�W���[
		CharacterManager* pCharacterMan_ = nullptr;

		// �}�b�v�`�b�v�}�l�[�W���[
		MapChipManager* pMapChipManager_ = nullptr;

		// �X�N���[���J����
		ScrollCamera scrollCamera_;

		// �]���p�r���[�v���W�F�N�V����
		ViewProjection transferVP_;

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
