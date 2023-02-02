#include "MyGame.h"
#include "Def.h"
#include "YGameSceneFactory.h"

#pragma region 名前空間宣言
using YBase::MyGame;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YScene;
using namespace YGame;
#pragma endregion 

bool MyGame::Initialize()
{
	// 基底クラス初期化処理
	if (YFramework::Initialize() == false) { return false; }

	sceneMan_->SetSceneFactory(new YGameSceneFactory());
	sceneMan_->Change("PLAY");

	return true;
}

void MyGame::Finalize()
{
	// 基底クラス終了処理
	YFramework::Finalize();
}

void MyGame::Update()
{
	// 基底クラス更新処理
	YFramework::Update();

	// ------------------- 終了処理 ------------------- //
	// ------------------------------------------------ //
}

void MyGame::Draw()
{
	// 描画準備
	dx_.PreDraw(ClearColor);

	// スクリーン設定セット
	screenDesc_.SetDrawCommand();

	// デスクリプターヒープセット
	descHeap_.SetDrawCommand();

	// シーン描画
	sceneMan_->Draw();

	// imgui描画
	imguiCon_.Draw();

	// 描画後処理
	dx_.PostDraw();
}
