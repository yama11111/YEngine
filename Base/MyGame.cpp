#include "MyGame.h"
#include "MathUtillity.h"
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
	YFramework::StaticInitialize({ SceneManager::GetInstance() });
	if (YFramework::Initialize() == false) { return false; }

#pragma region Base

	// Windows 初期化
	window_.Create(WindowTitle, WinSize.x_, WinSize.y_);

	// DirectX 初期化
	YDirectX::SetFPS(FixFPS);
	if (!dx_.Initialize(window_.HandleWindow(), WinSize)) { return false; }

	// Input 初期化
	inputMan_ = InputManager::GetInstance();
	inputMan_->Create(window_.HandleWindowInstance(), window_.PointerHandleWindow());

	// 乱数初期化
	Srand();

#pragma endregion

#pragma region Pipeline

	// デバイスポインタ
	ID3D12Device* pDev = dx_.Device();
	// コマンドリストポインタ
	ID3D12GraphicsCommandList* pCmdList = dx_.CommandList();

	// スクリーン設定
	ScreenDesc::StaticInitialize(pCmdList);
	screenDesc_.Initialize({ 0,0 }, WinSize);

	// GPUResource 静的初期化
	GPUResource::StaticInitialize(pDev);

	// デスクリプターヒープ (SRV, UAV, CBV)
	DescriptorHeap::StaticInitialize({ pDev, pCmdList });
	descHeap_.Initialize();

	// 定数バッファ静的初期化
	ConstBufferCommon::StaticInitialize({ pCmdList, &descHeap_ });

	// テクスチャマネージャー
	TextureManager::StaticInitialize({ pDev, pCmdList, &descHeap_ });

	// パイプライン静的初期化
	PipelineSet::StaticInitialize(pDev, pCmdList);

	// 頂点
	Vertices<Sprite2DCommon::VData>	::StaticInitialize(pCmdList);
	Vertices<Sprite3DCommon::VData>	::StaticInitialize(pCmdList);
	Vertices<ModelCommon::VData>	::StaticInitialize(pCmdList);

	// コモンクラス静的初期化
	Sprite2DCommon	::StaticInitialize({ &texMan_ });
	Sprite3DCommon	::StaticInitialize({ &texMan_ });
	ModelCommon		::StaticInitialize({ &texMan_ });

#pragma endregion

#pragma region Game

	// imgui初期化
	imguiCon_.Initialize({ window_.PointerHandleWindow(), pDev, dx_.BackBufferCount(), pCmdList });

	// オーディオ初期化
	audioMan_.Initialize();

	// シーン初期化
	BaseScene::StaticInitialize(&texMan_, &audioMan_);
	sceneMan_->SetSceneFactory(new YGameSceneFactory());
	sceneMan_->Change("PLAY");

#pragma endregion

	return true;
}

void MyGame::Finalize()
{
	// imguiをクリーン
	imguiCon_.Finalize();

	// ウィンドウクラスを登録解除
	window_.FinalProcess();

	// 基底クラス終了処理
	YFramework::Finalize();
}

void MyGame::Update()
{
	// input更新
	inputMan_->Update();

	// imgui受付開始
	imguiCon_.Begin();

	// 基底クラス更新処理
	YFramework::Update();
	
	// imgui受付終了
	imguiCon_.End();

	// ------------------- 終了処理 ------------------- //
	// ×ボタンで終了メッセージ
	if (window_.CheckMessage()) { isEnd_ = true; }
	// ESCキーで終了
	if (inputMan_->keys_->IsTrigger(DIK_ESCAPE)) { isEnd_ = true; }
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
