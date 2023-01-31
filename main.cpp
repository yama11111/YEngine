#include "YWindowsApp.h"
#include "YDirectX.h"
#include "ScreenDesc.h"
#include "InputManager.h"
#include "ImGuiContoroller.h"
#include "GameScene.h"
#include "Def.h"
#include <imgui.h>

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

	// Input 初期化
	InputManager* input = InputManager::GetInstance();
	input->Create(window.HandleWindowInstance(), window.PointerHandleWindow());

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

	// GPUResource 静的初期化
	GPUResource::StaticInitialize(pDev);

	// デスクリプターヒープ (SRV, UAV, CBV)
	DescriptorHeap::StaticInitialize({ pDev, pCmdList });
	DescriptorHeap descHeap;
	descHeap.Initialize();

	// 定数バッファ静的初期化
	ConstBufferCommon::StaticInitialize({ pCmdList, &descHeap });

	// テクスチャマネージャー
	TextureManager::StaticInitialize({ pDev, pCmdList, &descHeap });
	TextureManager texMan;

	// パイプライン静的初期化
	PipelineSet::StaticInitialize(pDev, pCmdList);

	// 頂点
	Vertices<Sprite2DCommon::VData>	::StaticInitialize(pCmdList);
	Vertices<Sprite3DCommon::VData>	::StaticInitialize(pCmdList);
	Vertices<ModelCommon::VData>	::StaticInitialize(pCmdList);

	// コモンクラス静的初期化
	Sprite2DCommon	::StaticInitialize({ &texMan });
	Sprite3DCommon	::StaticInitialize({ &texMan });
	ModelCommon		::StaticInitialize({ &texMan });

#pragma endregion

#pragma region Game

	// imgui初期化
	ImGuiContoroller imguiCon;
	imguiCon.Initialize({ window.PointerHandleWindow(), pDev, dx.BackBufferCount(), pCmdList});

	// オーディオ初期化
	AudioManager audioM;
	audioM.Initialize();

	// ゲームシーン初期化
	GameScene::StaticInitialize(&texMan, &audioM);
	GameScene game;
	game.Load();
	game.Initialize();

#pragma endregion

	char buf[100]{};
	float f = 0.0f;

	// ゲームループ
	while (true)
	{
		// -------------------- Update -------------------- //

		input->Update(); // input更新

		imguiCon.Begin(); // imgui受付開始

		game.Update(); // ゲームシーン更新

		ImGui::Text("Hello, world %d", 123);
		if (ImGui::Button("Save")) {}
		ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

		imguiCon.End(); // imgui受付終了

		// ------------------------------------------------ //

		// --------------------- Draw --------------------- //

		dx.PreDraw(ClearColor); // 描画準備

		screenDesc.SetDrawCommand(); // スクリーン設定セット

		descHeap.SetDrawCommand(); // デスクリプターヒープセット
		
		game.Draw(); // ゲームシーン描画

		imguiCon.Draw(); // imgui描画

		dx.PostDraw(); // 描画後処理

		// ------------------------------------------------ //

		// ------------------- 終了処理 ------------------- //

		// ×ボタンで終了メッセージ
		if (window.CheckMessage()) { break; }

		// ESCキーで終了
		if (input->keys_->IsTrigger(DIK_ESCAPE)) { break; }

		// ------------------------------------------------ //
	}

	// imguiをクリーン
	imguiCon.Finalize();

	// ウィンドウクラスを登録解除
	window.FinalProcess();

	return 0;
}