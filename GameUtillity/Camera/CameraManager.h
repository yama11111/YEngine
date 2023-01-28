#pragma once
#include "Camera.h"
#include "Lerp.h"
#include "Timer.h"

class CameraManager
{
private:
	// カメラ
	Camera camera_;
	// 追従フラグ
	bool isFollow_ = false;
	// 追従点ポインタ
	YMath::Vec3* pFollowPoint_ = nullptr;
public:
	// 初期化
	void Initialize();
	// 更新
	void Update();
private:
	// 追従更新
	void UpdateFollow();
public:
	// カメラシェイク
	void Shaking(const int swing, const int dekey);
	// ビュープロジェクション取得
	YGame::ViewProjection GetViewProjection();
	// 追従点ポインタ設定
	void SetFollowPoint(YMath::Vec3* pFollowPoint);
};

