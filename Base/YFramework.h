#pragma once
#include "SceneManager.h"
#include "TransitionManager.h"
#include "YWindowsApp.h"
#include "YDirectX.h"
#include "ScreenDesc.h"
#include "ImGuiManager.h"
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
		
		// ゲームルール
		YGame::WorldRuler worldRuler_;
		
		// imguiマネージャー
		ImGuiManager imguiMan_;
		
		// シーンマネージャー
		YScene::SceneManager* sceneMan_ = nullptr;
		
		// シーン遷移マネージャー
		YGame::TransitionManager* transitionMan_ = nullptr;
		
		// 終了フラグ
		bool isEnd_ = false;
	
	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <returns>成功したか</returns>
		virtual bool Initialize();

		/// <summary>
		/// 終了処理
		/// </summary>
		virtual void Finalize();

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update();
		
		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() = 0;
		
		/// <summary>
		/// 終了フラグ取得
		/// </summary>
		/// <returns>終了フラグ</returns>
		bool IsEnd() { return isEnd_; }

		/// <summary>
		/// 終了フラグ設定
		/// </summary>
		/// <param name="isEnd"> : 終了フラグ</param>
		void SetEnd(const bool isEnd) { isEnd_ = isEnd; }
	
	public:

		/// <summary>
		/// 実行
		/// </summary>
		void Run();
	
	public:
		
		YFramework() = default;
		
		virtual ~YFramework() = default;
	
	};
}
