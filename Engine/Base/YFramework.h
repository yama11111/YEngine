#pragma once
#include "SceneManager.h"
#include "YWindowsApp.h"
#include "YDirectX.h"
#include "ScreenDesc.h"
#include "PipelineManager.h"
#include "ParticleManager.h"
#include "ImGuiManager.h"
#include <memory>

namespace YBase
{
	class YFramework
	{
	
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
		/// 実行
		/// </summary>
		void Run();
	
	public:
		
		YFramework() = default;
		
		virtual ~YFramework() = default;

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
		
		// imguiマネージャー
		ImGuiManager imguiMan_;

		// パイプラインマネージャー
		YGame::PipelineManager* pPipelineMan_ = nullptr;
		
		// パーティクルマネージャー
		YGame::ParticleManager* pParticleMan_ = nullptr;
		
		// シーンマネージャー
		YGame::SceneManager* sceneMan_ = nullptr;
		
		// 終了フラグ
		bool isEnd_ = false;
	
	};
}
