#pragma once
#include "Model.h"
#include "Collider.h"
#include "MapChipCollider.h"

class MapChipPointer;

class Enemy : public Collision::Collider, public MapChipCollider
{
protected:
	// オブジェクト
	YGame::Object obj_;
	// スピード
	YMath::Vec3 speed_;
public:
	// リセット
	virtual void Reset() = 0;
	// 衝突時処理
	void OnCollision(const uint32_t attribute) override;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw(const YGame::ViewProjection& vp) = 0;
public:
	// 位置取得
	YMath::Vec3 Pos() const override { return obj_.pos_; };
	// 大きさ取得
	YMath::Vec3 Scale() const { return obj_.scale_; };
public:
	// 位置取得 (参照渡し)
	YMath::Vec3& PosRef() override { return obj_.pos_; }
	// スピード (参照渡し)
	YMath::Vec3& SpeedRef() override { return speed_; }
protected:
	// 静的マップチップポインタ
	static MapChipPointer* pMapChip_;
public:
	// 静的マップチップポインタ設定
	static void SetMapChipPointer(MapChipPointer* pMapChip);
};

