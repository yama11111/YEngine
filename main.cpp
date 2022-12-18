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
using namespace Game;

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

#pragma region Utillity

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
	RootParameterManager rpM;

	// 定数バッファ静的初期化
	ConstBuffer<TransformCBData>::StaticInitialize(pCmdList);
	ConstBuffer<TransformCBData>::SetRootParameterIndex(rpM.PushBackCBV());
	ConstBuffer<ColorCBData>::StaticInitialize(pCmdList);
	ConstBuffer<ColorCBData>::SetRootParameterIndex(rpM.PushBackCBV());
	ConstBuffer<MaterialCBData>::StaticInitialize(pCmdList);
	ConstBuffer<MaterialCBData>::SetRootParameterIndex(rpM.PushBackCBV());
	ConstBuffer<BillboardCBData>::StaticInitialize(pCmdList);
	ConstBuffer<BillboardCBData>::SetRootParameterIndex(rpM.PushBackCBV());

	// シェーダーリソースビュー
	SRVHeap::StaticInitialize(pDev, pCmdList);
	SRVHeap srvHeap;
	srvHeap.Create();
	// テクスチャマネージャー
	TextureManager::StaticInitialize(pDev, pCmdList, &srvHeap);
	TextureManager texM;
	texM.SetRootParameterIndex(rpM.PushBackTR());

	PipelineSet::StaticInitialize(pDev, pCmdList);

	// 頂点
	Vertices<SpriteVData>::StaticInitialize(pCmdList);
	Vertices<ModelVData>::StaticInitialize(pCmdList);
	Vertices<BillboardVData>::StaticInitialize(pCmdList);

	// 
	Sprite::StaticInitialize(&texM, rpM.Get());
	Material::StaticInitialize(&texM);
	Model::StaticInitialize(rpM.Get());
	Billboard::StaticInitialize(&texM, rpM.Get());

	AudioManager audioM;
	audioM.Initialize();

	GameScene::StaticInitialize(&texM, &audioM);
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

		srvHeap.SetDrawCommand(); // SRVヒープセット
		
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