#pragma once
#include "BaseScene.h"
#include "Level.h"

namespace YScene
{
	// �e�X�g�V�[��
	class TestScene : public BaseScene
	{

	private:

		YGame::Level* pLevel_ = nullptr;

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
