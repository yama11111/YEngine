#pragma once
#include "BaseScene.h"

namespace YGame
{
	class ResultScene :
		public BaseScene
	{


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
		ResultScene() = default;

		// �f�X�g���N�^
		~ResultScene() = default;

	};
}
