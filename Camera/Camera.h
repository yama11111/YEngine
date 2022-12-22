#pragma once
#include "Object.h"
#include "ViewProjection.h"
#include "Shake.h"

class Camera
{
public:
	// 位置
	YMath::Vec3 pos_;
	// 回転
	YMath::Vec3 rota_;
private:
	// オブジェクト
	YGame::Object obj_;
	// ビュープロジェクション
	YGame::ViewProjection vp_;
	// カメラシェイク
	YMath::Shake shake_;
public:
	// 初期化
	void Initialize(YGame::Object::Status state);
	// 初期化(カメラシェイク以外)
	void SetStatus(YGame::Object::Status state);
	// カメラシェイク
	void Shaking(const int swing, const int dekey);
	// trfm → vp
	void Update();
public:
	// ビュープロジェクション
	YGame::ViewProjection GetViewProjection();
	// カメラ向き
	YMath::Vec3 Verocity();
	// 揺れているか
	bool IsShake() { return shake_.IsShake(); }
};

