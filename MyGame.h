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
	};
}
