#include "YWindowsApp.h"
#include "YDirectX.h"
#include "ScreenDesc.h"
#include "InputManager.h"
#include "RootParameterManager.h"
#include "GameScene.h"
#include "Def.h"

using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#pragma region Base

	// Windows 初期化
	YWindowsApp window;
	window.Create(WindowTitle, WinSize.x_, WinSize.y_);

	// DirectX 初期化
	YDirectX::SetFPS(FixFPS);
	YDirectX dx;
	if (!dx.Initialize(window.HandleWindow(), WinSize)) { return 0; }

#pragma endregion

#pragma region Pipeline

	// デバイスポインタ
	ID3D12Device* pDev = dx.Device();
	// コマンドリストポインタ
	ID3D12GraphicsCommandList* pCmdList = dx.CommandList();

	// スクリーン設定
	ScreenDesc::StaticInitialize(pCmdList);
	ScreenDesc screenDesc;
	screenDesc.Initialize({ 0,0 }, WinSize);

	// Input 初期化
	InputManager* input = InputManager::GetInstance();
	input->Create(window.HandleWindowInstance(), window.PointerHandleWindow());

	// GPUResource 静的初期化
	GPUResource::StaticInitialize(pDev);

	// ルートパラメータ
	RootParameterManager rpMan;

	// デスクリプターヒープ (SRV, UAV, CBV)
	DescriptorHeap::StaticInitialize({ pDev, pCmdList });
	DescriptorHeap descHeap;
	descHeap.Initialize();

	// 定数バッファ静的初期化
	ConstBufferCommon::StaticInitialize({ pCmdList, &descHeap });
	ConstBuffer<TransformCBData>::StaticSetRootParamIndex(rpMan.PushBackCBV());
	ConstBuffer<ColorCBData>	::StaticSetRootParamIndex(rpMan.PushBackCBV());
	ConstBuffer<MaterialCBData>	::StaticSetRootParamIndex(rpMan.PushBackCBV());
	ConstBuffer<BillboardCBData>::StaticSetRootParamIndex(rpMan.PushBackCBV());

	// テクスチャマネージャー
	TextureManager::StaticInitialize({ pDev, pCmdList, &descHeap, rpMan.PushBackTexRegister() });
	TextureManager texMan;

	// パイプライン静的初期化
	PipelineSet::StaticInitialize(pDev, pCmdList);

	// 頂点
	Vertices<SpriteCommon::VData>	::StaticInitialize(pCmdList);
	Vertices<ModelCommon::VData>	::StaticInitialize(pCmdList);
	Vertices<BillboardCommon::VData>::StaticInitialize(pCmdList);

	// コモンクラス静的初期化
	SpriteCommon	::StaticInitialize({ &texMan, rpMan.Get() });
	Material::StaticInitialize(&texMan);
	ModelCommon		::StaticInitialize({ rpMan.Get() });
	BillboardCommon	::StaticInitialize({ &texMan, rpMan.Get() });

#pragma endregion

#pragma region Game

	AudioManager audioM;
	audioM.Initialize();

	GameScene::StaticInitialize(&texMan, &audioM);
	GameScene game;
	game.Load();
	game.Initialize();

#pragma endregion

	// ゲームループ
	while (true)
	{
		// -------------------- Update -------------------- //

		input->Update(); // input更新

		game.Update(); // ゲームシーン更新

		// ------------------------------------------------ //

		// --------------------- Draw --------------------- //

		dx.PreDraw(ClearColor); // 描画準備

		screenDesc.SetDrawCommand(); // スクリーン設定セット

		descHeap.SetDrawCommand(); // デスクリプターヒープセット
		
		game.Draw(); // ゲームシーン描画

		dx.PostDraw(); // 描画後処理

		// ------------------------------------------------ //

		// ------------------- 終了処理 ------------------- //

		// ×ボタンで終了メッセージ
		if (window.CheckMessage()) { break; }

		// ESCキーで終了
		if (input->keys_->IsTrigger(DIK_ESCAPE)) { break; }

		// ------------------------------------------------ //
	}

	// ウィンドウクラスを登録解除
	window.FinalProcess();

	return 0;
}