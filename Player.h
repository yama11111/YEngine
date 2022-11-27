#pragma once
#include "Model.h"
#include "Collider.h"

class Player : Collision::Collider
{
private:
	// オブジェクト
	Game::Object obj_;

	// ジャンプ回数
	int jumpCount_ = 0;
	// ジャンプ量
	float jumpPower_ = 0.0f;
	// 地面にいるか
	bool isLanding_ = false;
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
public:
	// ジャンプ
	void Jump();
	// 攻撃
	void Attack();
private:
	// ジャンプアップデート
	void UpdateJump();
	// 攻撃アップデート
	void UpdateAttack();
public:
	// 位置取得
	Math::Vec3 Pos() override { return obj_.pos_; };
private:
	// 静的モデルポインタ
	static Game::Model* pModel_;
	// 静的テクスチャインデックス
	static UINT tex_;
public:
	// 静的初期化ステータス
	struct StaticInitStatus
	{
		Game::Model* pModel_;// モデルポインタ
		UINT tex_;// テクスチャインデックス
	};
public:
	// 静的初期化
	static void StaticIntialize(const StaticInitStatus& state);
};

