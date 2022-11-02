#include "YWindowsApp.h"
#include "YDirectX.h"
#include "InputManager.h"
//#include "Game.h"
#include "ScreenDesc.h"
#include "Def.h"

using namespace DX;
using namespace Input;

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

	//PipelineState::StaticInit();
	//PipelineSet::StaticInit(dx->GetCommandList());
	//ShaderResourceView::StaticInit(dx->GetCommandList());

	//ConstBufferManager::StaticInit(dx->GetCommandList());
	//TextureManager::StaticInit();
	//Vertices::StaticInit(dx->GetCommandList());
	//Vertices2D::StaticInit(dx->GetCommandList());
	//Vertices3D::StaticInit(dx->GetCommandList());
	//Transform::StaticInit();
	//Sprite::StaticInit();
	//Model::StaticInit();


	//Game game;
	//game.Initialize();

	// ゲームループ
	while (true)
	{
		// ----- 毎フレーム処理 ----- //

		input->Update(); // input更新

		// -------------------- Update -------------------- //

		//game.Update();

		// ------------------------------------------------ //

		dx.PreDraw(CLEAR_COLOR); // 描画準備

		screenDesc.SetCommand(); // スクリーン設定セット
		
		// --------------------- Draw --------------------- //

		//game.Draw();

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