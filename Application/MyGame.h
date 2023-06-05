#pragma once
#include "YFramework.h"

namespace YBase
{
	class MyGame : public YFramework
	{

	private:

		bool shaderSwitch_ = false;
		YGame::PostEffect* pPostEffect_ = nullptr;
		std::unique_ptr<YGame::PostEffect::Object> postEffectObject_;

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
