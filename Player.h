#pragma once
#include "Model.h"
#include "Collider.h"
#include "Keys.h"

class Player : Collision::Collider
{
private:
	// オブジェクト
	Game::Object obj_;

	// キー
	Input::Keys* keys = nullptr;
public:
	// 初期化
	void Initialize();
	// リセット
	void Reset();
	// 衝突時処理
	void OnCollision(const uint32_t attribute) override;
	// 更新
	void Update();
	// 描画
	void Draw(const Game::ViewProjection& vp);
private:
	// ジャンプ
	void Jump();
public:
	// 位置取得
	Math::Vec3 Pos() override { return obj_.pos_; };
private:
	// 静的モデルポインタ
	static Game::Model* model_;
	// 静的テクスチャインデックス
	static UINT tex_;
public:
	// 静的初期化ステータス
	struct StaticInitStatus
	{
		Game::Model* model_;// モデルポインタ
		UINT tex_;// テクスチャインデックス
	};
public:
	// 静的初期化
	static void StaticIntialize(const StaticInitStatus& state);
};

