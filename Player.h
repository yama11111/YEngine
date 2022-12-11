#pragma once
#include "Model.h"
#include "Collider.h"
#include "MapChipCollider.h"

class Player : public Collision::Collider, public MapChipCollider
{
private:
	// オブジェクト
	Game::Object obj_;
	// スピード
	Math::Vec3 speed_;
	// ジャンプ回数
	int jumpCount_ = 0;
public:
	// 初期化
	void Initialize();
	// リセット
	void Reset();
	// 衝突時処理
	void OnCollision(const uint32_t attribute) override;
	// 更新
	void Update();
	// 移動量更新
	void UpdateMove();
	// 行列更新
	void UpdateMatrix();
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
	Math::Vec3 Pos() const override { return obj_.pos_; };
	// 大きさ取得
	Math::Vec3 Scale() const { return obj_.scale_; };
public:
	// 位置取得 (参照渡し)
	Math::Vec3& PosRef() override { return obj_.pos_; }
	// スピード (参照渡し)
	Math::Vec3& SpeedRef() override { return speed_; }
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

