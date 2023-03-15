#include "YFramework.h"
#include "MathUtillity.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言
using YBase::YFramework;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YScene;
using namespace YGame;
#pragma endregion

bool YFramework::Initialize()
{
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

	// ゲームルール初期化
	worldRuler_.Initailze();
	WorldRuleAdopter::StaticInitialize(&worldRuler_);
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
	BaseScene::StaticInitialize(&texMan_, &audioMan_, &worldRuler_);
	sceneMan_ = SceneManager::GetInstance();

#pragma endregion

	isEnd_ = false;

	return true;
}

void YFramework::Finalize()
{
	// imguiをクリーン
	imguiCon_.Finalize();

	// ウィンドウクラスを登録解除
	window_.FinalProcess();

	// シーン終了処理
	sceneMan_->Finalize();
}

void YFramework::Update()
{
	// input更新
	inputMan_->Update();

	// imgui受付開始
	imguiCon_.Begin();

	// ゲームルール更新処理
	worldRuler_.Update();

	// シーン更新処理
	sceneMan_->Update();

	// imgui受付終了
	imguiCon_.End();

	// ------------------- 終了処理 ------------------- //
	// ×ボタンで終了メッセージ
	if (window_.CheckMessage()) { isEnd_ = true; }
	// ESCキーで終了
	if (inputMan_->keys_->IsTrigger(DIK_ESCAPE)) { isEnd_ = true; }
	// ------------------------------------------------ //
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
