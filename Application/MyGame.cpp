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
	sceneExe_->SetFactory(new YGameSceneFactory(), new YGameTransitionFactory());

	// シーンエグゼクティブ初期化
	sceneExe_->Initialize(YGameSceneFactory::Play_, YGameTransitionFactory::Blackout_);

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
	// デスクリプターヒープセット
	descHeap_.SetDrawCommand();

	//pPostEffect_->StartRender();

	
	
	//pPostEffect_->EndRender();

	//pPostEffect_->SetDrawCommand(postEffectObject_.get());
	//pPostEffect_->SetDrawCommand(postEffectObject_.get(), PostEffect::ShaderType::eBloom);

	// 描画準備
	dx_.PreDraw(ClearColor);

	// スクリーン設定セット
	screenDesc_.SetDrawCommand();
	
	// ゲームシーン描画
	DrawGameScene();
	
	// ポストエフェクト描画
	PostEffect::Pipeline::StaticDraw();

	// ポストエフェクト描画セットクリア
	PostEffect::Pipeline::StaticClearDrawSet();

#ifdef _DEBUG

	// imgui描画
	imguiMan_.Draw();

#endif // DEBUG

	// 描画後処理
	dx_.PostDraw();
}

void MyGame::DrawGameScene()
{
	// シーン描画
	sceneExe_->Draw();

	// 描画場所の数だけ
	for (size_t i = 0; i < DrawLocationNum; i++)
	{
		// 変換
		DrawLocation location = static_cast<DrawLocation>(i);


		// モデル描画
		Model::Pipeline::StaticDraw(location);

		// スプライト3D描画
		Sprite3D::Pipeline::StaticDraw(location);

		// スプライト2D描画
		Sprite2D::Pipeline::StaticDraw(location);


		// モデル描画セットクリア
		Model::Pipeline::StaticClearDrawSet(location);

		// スプライト3D描画セットクリア
		Sprite3D::Pipeline::StaticClearDrawSet(location);

		// スプライト2D描画セットクリア
		Sprite2D::Pipeline::StaticClearDrawSet(location);
	}
}
