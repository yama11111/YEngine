#pragma once
#include "Camera.h"
#include "Lerp.h"
#include "Timer.h"
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"

namespace YGame
{
	class CameraManager
	{
	private:
		// カメラ
		Camera camera_;
		// 追従点
		YMath::Vector3* pFollowPoint_ = nullptr;
	public:
		// 初期化
		void Initialize(YMath::Vector3* pFollowPoint);
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
