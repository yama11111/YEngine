#pragma once
#include "BaseScene.h"

namespace YScene
{
	// �Q�[���V�[��
	class PlayScene : public BaseScene
	{

	public:

#pragma region ���\�[�X

		YGame::Model* pModel_ = nullptr;



#pragma endregion

#pragma region �Q�[���I�u�W�F�N�g

		std::unique_ptr<YGame::Model::Object> modelObj_;


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
