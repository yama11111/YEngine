#include "YWindows.h"
#include "YDirectX.h"
#include "DInput.h"
#include "Keys.h"
#include "VertexIndex.h"
#include "ConstBufferManager.h"
#include "TextureManager.h"
#include "DXDrawDesc.h"

#include "MatWorld.h"
#include "MatView.h"
#include "MatProjection.h"
#include "Calc.h"

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

	Vertices vert(
		{
			{{ -0.5f, -0.5f, 0.0f }}, // 左下
			{{ -0.5f,  0.5f, 0.0f }}, // 左上
			{{  0.5f, -0.5f, 0.0f }}, // 右下
		}
	);
	vert.Init();

	VertexIndex vtIdx(
		{
			// 前
			{{ -5.0f, -5.0f, -5.0f }}, // 左下
			{{ -5.0f,  5.0f, -5.0f }}, // 左上
			{{  5.0f, -5.0f, -5.0f }}, // 右下
			{{  5.0f,  5.0f, -5.0f }}, // 右上

			// 後
			{{ -5.0f, -5.0f,  5.0f }}, // 左下
			{{ -5.0f,  5.0f,  5.0f }}, // 左上
			{{  5.0f, -5.0f,  5.0f }}, // 右下
			{{  5.0f,  5.0f,  5.0f }}, // 右上

			// 左
			{{ -5.0f, -5.0f, -5.0f }}, // 左下
			{{ -5.0f, -5.0f,  5.0f }}, // 左上
			{{ -5.0f,  5.0f, -5.0f }}, // 右下
			{{ -5.0f,  5.0f,  5.0f }}, // 右上

			// 右
			{{  5.0f, -5.0f, -5.0f }}, // 左下
			{{  5.0f, -5.0f,  5.0f }}, // 左上
			{{  5.0f,  5.0f, -5.0f }}, // 右下
			{{  5.0f,  5.0f,  5.0f }}, // 右上

			// 下
			{{ -5.0f, -5.0f,  5.0f }}, // 左下
			{{ -5.0f, -5.0f, -5.0f }}, // 左上
			{{  5.0f, -5.0f,  5.0f }}, // 右下
			{{  5.0f, -5.0f, -5.0f }}, // 右上

			// 上
			{{ -5.0f,  5.0f,  5.0f }}, // 左下
			{{ -5.0f,  5.0f, -5.0f }}, // 左上
			{{  5.0f,  5.0f,  5.0f }}, // 右下
			{{  5.0f,  5.0f, -5.0f }}, // 右上
		},
		{
			// 前
			0, 1, 2, // 三角形1つ目
			2, 1, 3, // 三角形2つ目

			// 後
			6, 7, 4, // 三角形1つ目
			4, 7, 5, // 三角形2つ目

			// 左
			8, 9, 10, // 三角形1つ目
			10, 9, 11, // 三角形2つ目

			// 右
			14, 15, 12, // 三角形1つ目
			12, 15, 13, // 三角形2つ目

			// 下
			16, 17, 18, // 三角形1つ目
			18, 17, 19, // 三角形2つ目

			//// 上
			22, 23, 20, // 三角形1つ目
			20, 23, 21, // 三角形2つ目
		}
	);
	vtIdx.Init();

	VertexIndex vtIdx2(
		//{
		//	// 前
		//	{{   0.0f, 100.0f, 0.0f }, { 0.0f, 1.0f }}, // 左下
		//	{{   0.0f,   0.0f, 0.0f }, { 0.0f, 0.0f }}, // 左上
		//	{{ 100.0f, 100.0f, 0.0f }, { 1.0f, 1.0f }}, // 右下
		//	{{ 100.0f,   0.0f, 0.0f }, { 1.0f, 0.0f }}, // 右上
		//},
		{
			// 前
			{{ -50.0f, -50.0f, 0.0f }, { 0.0f, 1.0f }}, // 左下
			{{ -50.0f,  50.0f, 0.0f }, { 0.0f, 0.0f }}, // 左上
			{{  50.0f, -50.0f, 0.0f }, { 1.0f, 1.0f }}, // 右下
			{{  50.0f,  50.0f, 0.0f }, { 1.0f, 0.0f }}, // 右上
		},
		{
			// 前
			0, 1, 2, // 三角形1つ目
			2, 1, 3, // 三角形2つ目
		}
	);
	vtIdx2.Init();

	ConstBufferManager* cbM = ConstBufferManager::GetInstance();
	TextureManager* texM = TextureManager::GetInstance();
	DXSRVHeap* srvH = DXSRVHeap::GetInstance();

	ConstBufferMaterial cb;
	cbM->CreateCB(cb);
	ConstBufferTransform cb2;
	cbM->CreateCB(cb2);

	MatWorld mW;
	MatView mV;
	MatProjection mP(MatProjection::Perspective);

	cb2.cMapTrfm->mat = mW.m * mV.m * mP.m;

	UINT tex = texM->Create();
	UINT tex2 = texM->Load(L"Resources/player.png");

	texM->SetRootParameter();

	DXDrawDesc drawDesc;
	drawDesc.Create();

	// ゲームループ
	while (true)
	{
		// ----- DirectX 毎フレーム処理 ----- //

		// キーボード
		keys->Update();

		// -------------------- Update -------------------- //



		// ------------------------------------------------ //

		if (dx->PreDraw() == -1) return 0; // 描画準備

		// --------------------- Draw --------------------- //

		drawDesc.SetCommand();
		srvH->SetCommand();

		vtIdx2.SetCommand();
		cbM->SetCommand(cb);
		cbM->SetCommand(cb2);
		texM->SetCommand(tex);
		texM->SetCommand(tex2);
		vtIdx2.Draw();

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