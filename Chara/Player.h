#pragma once
#include "Character.h"
#include "Sprite2D.h"

class MapChipPointer;

class Player : public Character
{
private:
	YGame::ObjectSprite2D jump[2];
	// ジャンプ回数
	int jumpCount_ = 0;
public:
	// 初期化ステータス
	struct InitStatus
	{
		// 位置
		YMath::Vec3 pos_;
	};
public:
	// 初期化
	virtual void Initialize(const InitStatus& state);
	// リセット
	void Reset(const InitStatus& state);
	// 衝突時処理
	void OnCollision(const uint32_t attribute, const YMath::Vec3& pos) override;
	// 更新
	void Update();
	// 描画
	void Draw(const YGame::ViewProjection& vp);
	// 2D描画
	void Draw2D();
public:
	// ジャンプ
	void Jump();
	// 攻撃
	void Attack();
private:
	// 移動アップデート
	void UpdateMove();
	// ジャンプアップデート
	void UpdateJump();
	// 攻撃アップデート
	void UpdateAttack();
public:
	// 位置ポインタ取得
	YMath::Vec3* PosPointer() { return &obj_.pos_; }
private:
	// 静的モデルポインタ
	static YGame::Model* pModel_;
	// 静的スプライトポインタ
	static YGame::Sprite2D* pJump_;
	// 静的テクスチャインデックス
	static UINT tex_;
public:
	// 静的初期化ステータス
	struct StaticInitStatus
	{
		YGame::Model* pModel_;// モデルポインタ
		YGame::Sprite2D* pSprite_;
		UINT tex_;// テクスチャインデックス
	};
public:
	// 静的初期化
	static void StaticIntialize(const StaticInitStatus& state);
};

