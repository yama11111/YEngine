#pragma once
#include "Object.h"
#include "ViewProjection.h"
#include "Shake.h"

class Camera
{
public:
	// 位置
	Math::Vec3 pos_;
	// 回転
	Math::Vec3 rota_;
private:
	// オブジェクト
	Game::Object obj_;
	// ビュープロジェクション
	Game::ViewProjection vp_;
	// カメラシェイク
	Math::Shake shake_;
public:
	// 初期化
	void Initialize(Game::Object::Status state);
	// 初期化(カメラシェイク以外)
	void SetStatus(Game::Object::Status state);
	// カメラシェイク
	void Shaking(const int swing, const int dekey);
	// trfm → vp
	void Update();
public:
	// ビュープロジェクション
	Game::ViewProjection GetViewProjection();
	// カメラ向き
	Math::Vec3 Verocity();
	// 揺れているか
	bool IsShake() { return shake_.IsShake(); }
};

