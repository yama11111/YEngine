#pragma once
#include "BaseScene.h"
#include "BaseDrawer.h"

namespace YScene
{
	// �e�X�g�V�[��
	class TestScene : public BaseScene
	{

	private:

		YGame::Transform transform_;

		std::list<std::unique_ptr<YGame::BaseDrawer>> drawers_;

		YGame::ViewProjection vp_;

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
