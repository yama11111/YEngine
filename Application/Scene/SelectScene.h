#pragma once
#include "BaseScene.h"
#include "SelectDrawer.h"
#include "Camera.h"

namespace YGame
{
	// �Z���N�g�V�[��
	class SelectScene : public BaseScene
	{

	private:

		SelectDrawer selectDra_;

		uint32_t stageIndex_ = 0;

		// �r���[�v���W�F�N�V����
		ViewProjection transferVP_;
		Camera camera_;

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
		SelectScene() = default;
		
		// �f�X�g���N�^
		~SelectScene() = default;

	};
}

