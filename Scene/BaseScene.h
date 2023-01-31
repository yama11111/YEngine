#pragma once
#include "InputManager.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Model.h"
#include "AudioManager.h"
#include <memory>

namespace YScene
{
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
		static YInput::Keys* keys_;
		// マウス(シングルトン)
		static YInput::Mouse* mouse_;
		// パッド(シングルトン)
		static YInput::Pad* pad_;
	protected:
		// 静的テクスチャマネージャーポインタ
		static YGame::TextureManager* pTexManager_;
		// 静的オーディオマネージャーポインタ
		static YGame::AudioManager* pAudioManager_;
	public:
		// 静的初期化
		static void StaticInitialize(YGame::TextureManager* pTexManager, YGame::AudioManager* pAudioManager);
	};
}
