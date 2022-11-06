#include "YWindowsApp.h"
#include "YDirectX.h"
#include "InputManager.h"
#include "Game.h"
#include "ScreenDesc.h"
#include "Def.h"

using namespace DX;
using namespace Input;
using namespace Math;
using namespace Object;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windows 初期化
	YWindowsApp window;
	window.Create(L"LE2A_ヤマナカ_ルイ", WIN_SIZE);

	// DirectX 初期化
	YDirectX dx;
	if (!dx.Initialize(window.HandleWindow(), WIN_SIZE)) { return 0; }

	// スクリーン設定
	ScreenDesc::StaticInitialize(dx.CommandList());
	ScreenDesc screenDesc;
	screenDesc.Initialize({0,0}, WIN_SIZE);

	// Input 初期化
	InputManager* input = InputManager::GetInstance();
	input->Create(window.HandleWindowInstance(), window.PointerHandleWindow());

	GPUResource::StaticInitialize(dx.Device());
	ConstBufferManager::StaticInitialize(dx.CommandList());
	TextureManager::StaticInitialize(dx.Device(), dx.CommandList());
	PipelineSet::StaticInitialize(dx.Device(), dx.CommandList());
	
	Vertices<SpriteVData>::StaticInitialize(dx.CommandList());
	Vertices<ModelVData>::StaticInitialize(dx.CommandList());

	Game game;
	game.Initialize();

	// ゲームループ
	while (true)
	{
		// ----- 毎フレーム処理 ----- //

		input->Update(); // input更新

		// -------------------- Update -------------------- //

		game.Update();

		// ------------------------------------------------ //

		dx.PreDraw(CLEAR_COLOR); // 描画準備

		screenDesc.SetDrawCommand(); // スクリーン設定セット
		
		// --------------------- Draw --------------------- //

		game.Draw();

		// ------------------------------------------------ //

		dx.PostDraw(); // 描画後処理

		// ---------------------------------- //

		// ×ボタンで終了メッセージ
		if (window.CheckMessage()) { break; }

		// ESCキーで終了
		if (input->keys_->IsTrigger(DIK_ESCAPE)) { break; }
	}

	// ウィンドウクラスを登録解除
	window.FinalProcess();

	return 0;
}