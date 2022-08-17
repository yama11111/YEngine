#include "YWindows.h"
#include "YDirectX.h"
#include "DInput.h"
#include "Keys.h"
#include "Object2D.h"
#include "Object3D.h"
#include "DXDrawDesc.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
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

	TextureManager* texM = TextureManager::GetInstance();
	DXSRVHeap* srvH = DXSRVHeap::GetInstance();
	Model::StaticInit();
	Sprite::StaticInit();

	Sprite s1({ 128.0f, 128.0f });
	Model m1{};

	Object2D obj(&s1);
	Object3D obj2(&m1);
	MatViewProjection vp;

	UINT tex2 = texM->Load(L"Resources/player.png");
	UINT tex = texM->Load(L"Resources/enemy.png");

	srvH->SetRootParameter();

	DXDrawDesc drawDesc;
	drawDesc.Create();

	// ゲームループ
	while (true)
	{
		// ----- DirectX 毎フレーム処理 ----- //

		// キーボード
		keys->Update();

		// -------------------- Update -------------------- //

		obj2.mW.rota.x += keys->Vertical() * 0.05f;
		obj2.mW.rota.y -= keys->Horizontal() * 0.05f;

		obj.Update();
		obj2.Update();

		// ------------------------------------------------ //

		if (dx->PreDraw() == -1) return 0; // 描画準備

		// --------------------- Draw --------------------- //

		drawDesc.SetCommand();
		srvH->SetDescriptorHeaps();

		obj.Draw(tex);
		obj2.Draw(vp, tex2);

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