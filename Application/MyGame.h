#pragma once
#include "YFramework.h"

namespace YBase
{
	class MyGame : public YFramework
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <returns>����������</returns>
		bool Initialize() override;
		
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

	private:

		/// <summary>
		/// �p�C�v���C��������
		/// </summary>
		void InitializePipelines();

		/// <summary>
		/// �p�[�e�B�N��������
		/// </summary>
		void InitializeParticles();

		/// <summary>
		/// �}�b�v�f�[�^�ǂݍ���
		/// </summary>
		void LoadMapData();

		/// <summary>
		/// �`��N���X�ǂݍ���
		/// </summary>
		void LoadDrawer();

	};
}
