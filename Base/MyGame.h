#pragma once
#include "YFramework.h"
#include "YWindowsApp.h"
#include "YDirectX.h"
#include "ScreenDesc.h"
#include "InputManager.h"
#include "ImGuiContoroller.h"
#include "GameScene.h"
#include <memory>

namespace YBase
{
	class MyGame : public YFramework
	{
	private:
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
		// シーン
		std::unique_ptr<YScene::BaseScene> scene_;
	public:
		// 初期化
		bool Initialize() override;
		// 終了処理
		void Finalize() override;
		// 更新
		void Update() override;
		// 描画
		void Draw() override;
	};
}
