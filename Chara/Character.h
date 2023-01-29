#pragma once
#include "CharaStatus.h"
#include "Collider.h"
#include "MapChipCollider.h"
#include "SlimeActor.h"
#include "HitActor.h"
#include "ParticleManager.h"

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
	YGame::ObjectModel obj_;
	// スピード
	YMath::Vec3 speed_;
	// 

public:
	// 初期化
	void InitializeCharacter(YGame::ObjectModel::Status state);
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
	// 静的パーティクルマネージャーポインタ
	static YParticle::ParticleManager* pParticleMan_;
public:
	// 静的初期化設定
	struct StaticInitStatus 
	{
		MapChipPointer* pMapChip_;
		YParticle::ParticleManager* pParticleMan_;
	};
public:
	// 静的マップチップポインタ設定
	static void SetMapChipPointer(const StaticInitStatus& state);
};

