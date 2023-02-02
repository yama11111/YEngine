#pragma once
#include "SceneManager.h"
#include "YWindowsApp.h"
#include "YDirectX.h"
#include "ScreenDesc.h"
#include "ImGuiContoroller.h"
#include <memory>

namespace YBase
{
	class YFramework
	{
	protected:
		// WindowsAPI
		YWindowsApp window_;
		// DirectX12
		YDX::YDirectX dx_;
		// inputマネージャー
		YInput::InputManager* inputMan_ = nullptr;
		// スクリーン設定
		YDX::ScreenDesc screenDesc_;
		// デスクリプターヒープ (SRV, UAV, CBV)
		YDX::DescriptorHeap descHeap_;
		// テクスチャマネージャー
		YGame::TextureManager texMan_;
		// audioマネージャー
		YGame::AudioManager audioMan_;
		// imguiマネージャー
		ImGuiContoroller imguiCon_;
		// シーンマネージャー
		YScene::SceneManager* sceneMan_ = nullptr;
		// 終了フラグ
		bool isEnd_ = false;
	public:
		// 初期化
		virtual bool Initialize();
		// 終了処理
		virtual void Finalize();
		// 更新
		virtual void Update();
		// 描画
		virtual void Draw() = 0;
		// 終了フラグ取得
		virtual bool IsEnd() { return isEnd_; }
	public:
		// 実行
		void Run();
	public:
		YFramework() = default;
		virtual ~YFramework() = default;
	};
}
