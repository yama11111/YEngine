#pragma once
#include "BaseScene.h"

namespace YScene
{
	// �e�X�g�V�[��
	class TestScene : public BaseScene
	{

	private:

#pragma region ���\�[�X

#pragma endregion


#pragma region �Q�[���I�u�W�F�N�g

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
		TestScene() = default;
		
		// �f�X�g���N�^
		~TestScene() = default;

	};
}
