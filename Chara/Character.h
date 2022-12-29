#pragma once
#include "Object.h"
#include "CharaStatus.h"
#include "Collider.h"
#include "MapChipCollider.h"
#include "SlimeActor.h"
#include "HitActor.h"

class MapChipPointer;

class Character : 
	public CharaStatus, 
	public YCollision::Collider, 
	public MapChipCollider, 
	public YActor::SlimeActor,
	public YActor::HitActor
{
protected:
	// オブジェクト
	YGame::Object obj_;
	// スピード
	YMath::Vec3 speed_;
public:
	// 初期化
	void InitializeCharacter(YGame::Object::Status state);
	// 重力とマップチップアタリ判定とアニメーション
	void UpdateGravity();
	// 更新
	void UpdateCharacter();
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

