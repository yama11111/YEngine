#include "YFramework.h"
#include "MathUtil.h"
#include "Def.h"
#include <cassert>

#include "BaseConstBuffer.h"
#include "DefaultConstBuffer.h"
#include "DefaultGraphic.h"
#include "PipelineManager.h"

#pragma region 名前空間宣言

using YBase::YFramework;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
using namespace YGame;

#pragma endregion

bool YFramework::Initialize()
{
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


	// デバイスポインタ
	ID3D12Device* pDev = dx_.DevicePtr();
	// コマンドリストポインタ
	ID3D12GraphicsCommandList* pCmdList = dx_.CommandListPtr();

	// スクリーン設定
	ScreenDesc::StaticInitialize(pCmdList);
	screenDesc_.Initialize({ 0,0 }, WinSize);

	// GPUResource 静的初期化
	GPUResource::StaticInitialize(pDev);

	// デスクリプターヒープ (SRV, UAV, CBV)
	DescriptorHeap::StaticInitialize(pDev, pCmdList);
	descHeap_.Initialize();

	// 頂点
	VertexCommon::StaticInitialize(pCmdList);

	// 定数バッファ静的初期化
	ConstBufferCommon::StaticInitialize(pCmdList, &descHeap_);
	DefaultConstBuffer::StaticInitialize();

	// テクスチャ静的初期化
	Texture::Common::StaticInitialize(pDev, pCmdList, &descHeap_);
	Texture::AllClear();

	// ポストエフェクト
	PostEffect::StaticInitialize(pDev, pCmdList);

	// パイプライン静的初期化
	Pipeline::StaticInitialize(pDev, pCmdList);

	// FBXLoader読み込み
	Model::FbxLoader::StaticInitialize();

	DefaultGraphic::LoadResource();

	// imgui初期化
	imguiMan_.Initialize({ window_.HandleWindow(), pDev, pCmdList, &descHeap_, dx_.BackBufferCount() });

	// オーディオ初期化
	Audio::Base::StaticInitialize();
	Audio::AllClear();

	// シーン初期化
	BaseScene::StaticInitialize();
	
	sceneMan_ = SceneManager::GetInstance();
	sceneMan_->SetDescriptorHeapPointer(&descHeap_);
	
	pPipelineMan_ = PipelineManager::GetInstance();
	pPipelineMan_->Clear();

	pParticleMan_ = ParticleManager::GetInstance();
	pParticleMan_->Clear();

	isEnd_ = false;

	return true;
}

void YFramework::Finalize()
{
	// FBXLoader開放
	Model::FbxLoader::StaticFinalize();

	// imguiをクリーン
	imguiMan_.Finalize();

	// ウィンドウクラスを登録解除
	window_.FinalProcess();

	// シーン終了処理
	SceneManager::GetInstance()->Finalize();

	ParticleManager::GetInstance()->Clear();

	PipelineManager::GetInstance()->Clear();
	
	// リソース全クリア
	PostEffect::AllClear();
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

	// シーン更新処理
	sceneMan_->Update();

	// パーティクル更新
	pParticleMan_->Update();

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
		if (isEnd_) { break; }
	}

	// 終了処理
	Finalize();
}
