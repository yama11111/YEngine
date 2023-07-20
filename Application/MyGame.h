#pragma once
#include "YFramework.h"
#include "PipelineManager.h"

namespace YBase
{
	class MyGame : public YFramework
	{

	private:

		YGame::PipelineManager* pipelineMan_ = nullptr;

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
		/// �Q�[���V�[���`��
		/// </summary>
		void DrawGameScene();

	};
}
