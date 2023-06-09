#pragma once
#include "BaseScene.h"
#include "MapChipManager.h"
#include "GameCharacterManager.h"

namespace YScene
{
	// �Q�[���V�[��
	class PlayScene : public BaseScene
	{

	public:

#pragma region ���\�[�X


#pragma endregion

#pragma region �Q�[���I�u�W�F�N�g

		// �L�����N�^�[�}�l�[�W���[
		std::unique_ptr<YGame::GameCharacterManager> gameCharacterManager_;

		// �}�b�v�`�b�v�}�l�[�W���[
		YGame::MapChipManager* pMapChipManager_ = nullptr;

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
		PlayScene() = default;

		// �f�X�g���N�^
		~PlayScene() = default;

	};
}
