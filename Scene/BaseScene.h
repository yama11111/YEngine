#pragma once
#include "InputManager.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Model.h"
#include "AudioManager.h"
#include "WorldRuler.h"
#include <memory>

namespace YScene
{
	// 基底シーンクラス
	class BaseScene
	{
	public:
		// 読み込み
		virtual void Load() = 0;
		// 初期化
		virtual void Initialize() = 0;
		// 終了処理
		virtual void Finalize() = 0;
		// 更新
		virtual void Update() = 0;
		// 描画
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
		// 静的テクスチャマネージャーポインタ(シングルトン)
		static YGame::TextureManager* spTexManager_;
		// 静的オーディオマネージャーポインタ(シングルトン)
		static YGame::AudioManager* spAudioManager_;
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
