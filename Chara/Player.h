#pragma once
#include "Character.h"
#include "Model.h"

class MapChipPointer;

class Player : public Character
{
private:
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
	void OnCollision(const uint32_t attribute) override;
	// 更新
	void Update();
	// 描画
	void Draw(const YGame::ViewProjection& vp);
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
private:
	// 静的モデルポインタ
	static YGame::Model* pModel_;
	// 静的テクスチャインデックス
	static UINT tex_;
public:
	// 静的初期化ステータス
	struct StaticInitStatus
	{
		YGame::Model* pModel_;// モデルポインタ
		UINT tex_;// テクスチャインデックス
	};
public:
	// 静的初期化
	static void StaticIntialize(const StaticInitStatus& state);
};

