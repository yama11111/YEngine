#include "YFramework.h"
#include <cassert>

using YBase::YFramework;

YScene::SceneManager* YFramework::sceneMan_ = nullptr;

bool YFramework::Initialize()
{
	isEnd_ = false;

	return true;
}

void YFramework::Finalize()
{
	sceneMan_->Finalize();
}

void YFramework::Update()
{
	sceneMan_->Update();
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

void YFramework::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.sceneMan_);
	sceneMan_ = state.sceneMan_;
}
