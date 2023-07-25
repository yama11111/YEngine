#pragma once
#include "BaseScene.h"

#include "Smoke.h"
#include "Floor.h"

namespace YScene
{
	class TaskScene : public BaseScene
	{
		int a = 0;

		YGame::Smoke smoke_;

		YGame::Floor floor_;

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
		TaskScene() = default;

		// �f�X�g���N�^
		~TaskScene() = default;

	};
}
