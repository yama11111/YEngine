#include "YFramework.h"
#include "MathUtillity.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言

using YBase::YFramework;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YScene;
using namespace YGame;

#pragma endregion

bool YFramework::Initialize()
{
#pragma region Base

	// Windows 初期化
	window_.Create(WindowTitle, WinSize.x_, WinSize.y_);

	// DirectX 初期化
	YDirectX::SetFPS(FixFPS);
	if (!dx_.Initialize(window_.HandleWindow(), WinSize)) { return false; }

	// Input 初期化
	inputMan_ = InputManager::GetInstance();
	inputMan_->Create(window_.HandleWindowInstance(), window_.PointerHandleWindow());

	// 乱数初期化
	Srand();

	// ゲームルール初期化
	worldRuler_.Initailze();
	WorldRuleAdopter::StaticInitialize(&worldRuler_);

#pragma endregion

#pragma region Pipeline

	// デバイスポインタ
	ID3D12Device* pDev = dx_.Device();
	// コマンドリストポインタ
	ID3D12GraphicsCommandList* pCmdList = dx_.CommandList();

	// スクリーン設定
	ScreenDesc::StaticInitialize(pCmdList);
	screenDesc_.Initialize({ 0,0 }, WinSize);

	// GPUResource 静的初期化
	GPUResource::StaticInitialize(pDev);

	// デスクリプターヒープ (SRV, UAV, CBV)
	DescriptorHeap::StaticInitialize(pDev, pCmdList);
	descHeap_.Initialize();

	// 定数バッファ静的初期化
	ConstBufferCommon::StaticInitialize(pCmdList, &descHeap_);

	// テクスチャ静的初期化
	Texture::Base::StaticInitialize(pDev, pCmdList, &descHeap_);
	Texture::AllClear();

	// パイプライン静的初期化
	PipelineSet::StaticInitialize(pDev, pCmdList);

	// 頂点
	VertexCommon::StaticInitialize(pCmdList);

	// コモンクラス静的初期化
	Sprite2D::Pipeline::StaticInitialize();
	Sprite3D::Pipeline::StaticInitialize();
	Model::Pipeline::StaticInitialize();

	// オブジェクトデフォルト値静的初期化
	Sprite2DObject::Default::StaticInitialize();
	Sprite3DObject::Default::StaticInitialize();
	ModelObject::Default::StaticInitialize();

#pragma endregion

#pragma region Game

	// imgui初期化
	imguiMan_.Initialize({ window_.HandleWindow(), pDev, pCmdList, &descHeap_, dx_.BackBufferCount() });

	// オーディオ初期化
	Audio::Base::StaticInitialize();
	Audio::AllClear();

	// シーン遷移初期化
	TransitionManager::StaticInitialize();
	transitionMan_ = TransitionManager::GetInstance();
	transitionMan_->Initialize();

	// シーン初期化
	BaseScene::StaticInitialize(&worldRuler_);
	
	sceneMan_ = SceneManager::GetInstance();
	sceneMan_->SetDescriptorHeapPointer(&descHeap_);

#pragma endregion

	isEnd_ = false;

	return true;
}

void YFramework::Finalize()
{
	// imguiをクリーン
	imguiMan_.Finalize();

	// ウィンドウクラスを登録解除
	window_.FinalProcess();

	// シーン終了処理
	sceneMan_->Finalize();

	// リソース全クリア
	Model::AllClear();
	Sprite2D::AllClear();
	Sprite3D::AllClear();
	Texture::AllClear();
	Audio::AllClear();
}

void YFramework::Update()
{
	// imgui受付開始
	imguiMan_.Begin();
	
	// input更新
	inputMan_->Update();

	// ゲームルール更新処理
	worldRuler_.Update();

	// シーン遷移更新
	transitionMan_->Update();

	// シーン更新処理
	sceneMan_->Update();

	// デスクリプタカウント表示
	descHeap_.ShowCount();

	// imgui受付終了
	imguiMan_.End();

	// ------------------- 終了処理 ------------------- //
	
	// ×ボタンで終了メッセージ
	if (window_.CheckMessage()) { isEnd_ = true; }

	// シーンマネージャー終了フラグ
	if (sceneMan_->IsEnd()) { isEnd_ = true; }

	// ------------------------------------------------ //
}

void YFramework::Run()
{
	// 初期化
	bool isSuccess = Initialize();

	// ゲームループ
	while (isSuccess)
	{
		// 更新
		Update();

		// 描画
		Draw();

		// 終了
		if (IsEnd()) { break; }
	}

	// 終了処理
	Finalize();
}
