#include "YWindows.h"
#include "YDirectX.h"
#include "DInput.h"
#include "Keys.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windows 初期化
	YWindows* win = YWindows::GetInstance();
	win->Create(L"LE2A_ヤマナカ_ルイ_AL3");

	// DirectX 初期化
	YDirectX* dx = YDirectX::GetInstance();
	if (dx->Init(win->HandleWindow()) == -1) return 0;

	// Input 初期化
	DInput* input = DInput::GetInstance();
	input->Init(win->HandleWindowInstance(), win->HandleWindow());
	Keys* keys = Keys::GetInstance();

	// ゲームループ
	while (true)
	{
		// ----- DirectX 毎フレーム処理 ----- //

		// キーボード
		keys->Update();

		// -------------------- Update -------------------- //


		// ------------------------------------------------ //

		//if (dx->PreDraw() == -1) return 0; // 描画準備

		// --------------------- Draw --------------------- //


		// ------------------------------------------------ //

		if (dx->PostDraw() == -1) return 0; // 描画後処理

		// ---------------------------------- //

		// ×ボタンで終了メッセージ
		if (win->CheckMessage()) break;

		// ESCキーで終了
		if (keys->IsTrigger(DIK_ESCAPE)) break;
	}

	// ウィンドウクラスを登録解除
	win->FinalProcess();

	return 0;
}