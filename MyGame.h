#pragma once
#include "YFramework.h"

namespace YBase
{
	class MyGame : public YFramework
	{
	public:
		// ������
		bool Initialize() override;
		// �I������
		void Finalize() override;
		// �X�V
		void Update() override;
		// �`��
		void Draw() override;
	};
}
