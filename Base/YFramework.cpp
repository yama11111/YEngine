#include "YFramework.h"

using YBase::YFramework;

bool YFramework::Initialize()
{
	isEnd_ = false;

	return true;
}

void YFramework::Finalize()
{
}

void YFramework::Update()
{
}

void YFramework::Run()
{
	// ������
	bool isSuccess = Initialize();

	// �Q�[�����[�v
	while (isSuccess)
	{
		// �X�V
		Update();

		// �`��
		Draw();

		// �I��
		if (IsEnd()) { break; }
	}

	// �I������
	Finalize();
}
