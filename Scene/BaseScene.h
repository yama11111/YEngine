#pragma once
#include "InputManager.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Model.h"
#include "Audio.h"
#include "WorldRuler.h"
#include <memory>

namespace YScene
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
		static YInput::Keys* sKeys_;
		
		// マウス(シングルトン)
		static YInput::Mouse* sMouse_;
		
		// パッド(シングルトン)
		static YInput::Pad* sPad_;
	
	protected:
		
		// 静的ゲームルールポインタ
		static YGame::WorldRuler* spWorldRuler_;
	
	public:
		
		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pWorldRuler"> : ゲームルールポインタ</param>
		static void StaticInitialize(YGame::WorldRuler* pWorldRuler);
	
	};
}
