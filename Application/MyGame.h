#pragma once
#include "YFramework.h"

namespace YBase
{
	class MyGame : public YFramework
	{

	private:

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

	public:

		/// <summary>
		/// �Q�[���V�[���`��
		/// </summary>
		void DrawGameScene();

	};
}
