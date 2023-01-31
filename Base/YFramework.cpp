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
