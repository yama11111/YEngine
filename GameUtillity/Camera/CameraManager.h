#pragma once
#include "Camera.h"
#include "Lerp.h"
#include "Timer.h"
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"

namespace YGame
{
	// カメラマネージャーコモンクラス
	class CameraManagerCommon
	{
	private:
		// キー(シングルトン)
		static YInput::Keys* keys_;
		// マウス(シングルトン)
		static YInput::Mouse* mouse_;
		// パッド(シングルトン)
		static YInput::Pad* pad_;
	public:
		// 静的初期化
		static void StaticInitialize();
	};

	// カメラマネージャー
	class CameraManager : private CameraManagerCommon
	{
	private:
		// カメラ
		Camera camera_;
		// 追従点
		YMath::Vector3* pFollowPoint_ = nullptr;
	public:
		// 初期化用ステータス
		struct InitStatus
		{
			// トランスフォーム設定ステータス
			Transform::Status traState_;
			// 追従点ポインタ
			YMath::Vector3* pFollowPoint_ = nullptr;
			// 追従するか
			bool isFollow_ = false;
		};
	public:
		// 初期化
		void Initialize(const std::vector<InitStatus>& statuses);
		// 更新
		void Update();
	public:
		// カメラシェイク
		void Shaking(const int swing, const int dekey);
		// ビュープロジェクション取得
		ViewProjection GetViewProjection();
		// 追従点ポインタ設定
		void SetFollowPoint(YMath::Vector3* pFollowPoint);
	};
}
