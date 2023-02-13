#pragma once
#include "Camera.h"
#include "Lerp.h"
#include "Timer.h"
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"

namespace YCamera
{
	class CameraManager
	{
	private:
		// カメラ
		Camera camera_;
	public:
		// 初期化
		void Initialize();
		// 更新
		void Update();
	public:
		// カメラシェイク
		void Shaking(const int swing, const int dekey);
		// ビュープロジェクション取得
		YGame::ViewProjection GetViewProjection();
		// 追従点ポインタ設定
		void SetFollowPoint(YMath::Vector3* pFollowPoint);
	private:
		// キー(シングルトン)
		static YInput::Keys* keys_;
		// マウス(シングルトン)
		static YInput::Mouse* mouse_;
		// パッド(シングルトン)
		static YInput::Pad* pad_;
	public:
		static void StaticInitialize();
	};
}
