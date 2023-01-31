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
	// 初期化
	bool isSuccess = Initialize();

	// ゲームループ
	while (isSuccess)
	{
		// 更新
		Update();

		// 描画
		Draw();

		// 終了
		if (IsEnd()) { break; }
	}

	// 終了処理
	Finalize();
}

void YFramework::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.sceneMan_);
	sceneMan_ = state.sceneMan_;
}
