#include "MyGame.h"
#include "Def.h"
#include "YGameSceneFactory.h"
#include "YGameTransitionFactory.h"

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

	// シーンファクトリー設定
	sceneMan_->SetSceneFactory(new YGameSceneFactory());
	// 遷移ファクトリー設定
	sceneMan_->SetTransitionFactory(new YGameTransitionFactory());

	// シーンマネージャー初期化
	sceneMan_->Initialize("TEST");

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

	// シーン遷移描画
	transitionMan_->Draw();

#ifdef _DEBUG

	// imgui描画
	imguiMan_.Draw();

#endif // DEBUG

	// 描画後処理
	dx_.PostDraw();
}
