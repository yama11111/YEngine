#include "YWindowsApp.h"
#include "YDirectX.h"
#include "ScreenDesc.h"
#include "InputManager.h"
#include "RootParameterManager.h"
#include "GameScene.h"
#include "Def.h"

using namespace DX;
using namespace Input;
using namespace Math;
using namespace Game;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windows 初期化
	YWindowsApp window;
	window.Create(L"LE2A_ヤマナカ_ルイ", WIN_SIZE);

	// DirectX 初期化
	YDirectX::SetFPS(FIX_FPS);
	YDirectX dx;
	if (!dx.Initialize(window.HandleWindow(), WIN_SIZE)) { return 0; }

	ID3D12Device* pDev = dx.Device();
	ID3D12GraphicsCommandList* pCmdList = dx.CommandList();

	// スクリーン設定
	ScreenDesc::StaticInitialize(pCmdList);
	ScreenDesc screenDesc;
	screenDesc.Initialize({ 0,0 }, WIN_SIZE);

	// Input 初期化
	InputManager* input = InputManager::GetInstance();
	input->Create(window.HandleWindowInstance(), window.PointerHandleWindow());

	GPUResource::StaticInitialize(pDev);

	RootParameterManager rpM;

	ConstBuffer<TransformCBData>::StaticInitialize(pCmdList);
	ConstBuffer<TransformCBData>::SetRootParameterIndex(rpM.PushBackCBV());
	ConstBuffer<ColorCBData>::StaticInitialize(pCmdList);
	ConstBuffer<ColorCBData>::SetRootParameterIndex(rpM.PushBackCBV());
	ConstBuffer<MaterialCBData>::StaticInitialize(pCmdList);
	ConstBuffer<MaterialCBData>::SetRootParameterIndex(rpM.PushBackCBV());

	SRVHeap::StaticInitialize(pDev, pCmdList);
	SRVHeap srvHeap;
	srvHeap.Create();
	TextureManager::StaticInitialize(pDev, pCmdList, &srvHeap);
	TextureManager texM;
	texM.SetRootParameterIndex(rpM.PushBackTR());

	PipelineSet::StaticInitialize(pDev, pCmdList);

	Vertices<SpriteVData>::StaticInitialize(pCmdList);
	Vertices<ModelVData>::StaticInitialize(pCmdList);

	Sprite::StaticInitialize(&texM, rpM.Get());
	Material::StaticInitialize(&texM);
	Model::StaticInitialize(rpM.Get());

	AudioManager audioM;
	audioM.Initialize();

	GameScene::StaticInitialize(&texM, &audioM);
	GameScene game;
	game.Initialize();

	// ゲームループ
	while (true)
	{
		// -------------------- Update -------------------- //

		input->Update(); // input更新

		game.Update(); // ゲームシーン更新

		// ------------------------------------------------ //

		// --------------------- Draw --------------------- //

		dx.PreDraw(CLEAR_COLOR); // 描画準備

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