#include "YWindowsApp.h"
#include "YDirectX.h"
//#include "InputManager.h"
//#include "Game.h"
//#include "ScreenDesc.h"
#include "Def.h"

//using namespace DX;
//using namespace DX::GPUResource;
//using namespace DX::Utility;
//using namespace Input;
//using namespace Math;
//using namespace Object;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windows 初期化
	YWindowsApp window;
	window.Create(L"LE2A_ヤマナカ_ルイ", WIN_SIZE.x, WIN_SIZE.y);

	// DirectX 初期化
	YDirectX dx;
	if (!dx.Initialize(window.HandleWindow(), WIN_SIZE.x, WIN_SIZE.y)) return 0;

	//// Input 初期化
	//InputManager* input = InputManager::GetInstance();
	//input->Init(win->HandleWindowInstance(), win->HandleWindow());
	//Keys* keys = Keys::GetInstance();
	//Mouse* mouse = Mouse::GetInstance();

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

	//ScissorRect::StaticInit(dx->GetCommandList());
	//Viewport::StaticInit(dx->GetCommandList());
	//ScreenDesc screenDesc;
	//screenDesc.Set();

	//Game game;
	//game.Initialize();

	// ゲームループ
	while (true)
	{
		// ----- DirectX 毎フレーム処理 ----- //

		//// キーボード
		//keys->Update();
		//// マウス
		//mouse->Update(win->HandleWindow());

		// -------------------- Update -------------------- //

		//game.Update();

		// ------------------------------------------------ //

		dx.PreDraw(CLEAR_COLOR.r, CLEAR_COLOR.g ,CLEAR_COLOR.b ,CLEAR_COLOR.a); // 描画準備

		// --------------------- Draw --------------------- //
		//screenDesc.SetCommand();

		//game.Draw();

		// ------------------------------------------------ //

		dx.PostDraw(); // 描画後処理

		// ---------------------------------- //

		// ×ボタンで終了メッセージ
		if (window.CheckMessage()) break;

		// ESCキーで終了
		//if (keys->IsTrigger(DIK_ESCAPE)) break;
	}

	// ウィンドウクラスを登録解除
	window.FinalProcess();

	return 0;
}