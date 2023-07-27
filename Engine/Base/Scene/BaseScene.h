#pragma once
#include "InputManager.h"
#include "Transform.h"
#include "Camera.h"
#include "PipelineManager.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Model.h"
#include "PostEffect.h"
#include "Audio.h"
#include <memory>

namespace YGame
{
	// 基底シーンクラス
	class BaseScene
	{
	
	public:
		
		/// <summary>
		/// 読み込み
		/// </summary>
		virtual void Load() = 0;
		
		/// <summary>
		/// 初期化
		/// </summary>
		virtual void Initialize() = 0;
		
		/// <summary>
		/// 終了処理
		/// </summary>
		virtual void Finalize() = 0;

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() = 0;
		
		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() = 0;
	
	public:
		
		// コンストラクタ
		BaseScene() = default;
		
		// デストラクタ
		virtual ~BaseScene() = default;
	
	protected:
		
		// キー(シングルトン)
		static YInput::Keys* spKeys_;
		
		// マウス(シングルトン)
		static YInput::Mouse* spMouse_;
		
		// パッド(シングルトン)
		static YInput::Pad* spPad_;
		
		// パイプラインマネージャー
		static PipelineManager* spPipelineMan_;
	
	public:
		
		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();
	
	};
}
