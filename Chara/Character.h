#pragma once
#include "CharaStatus.h"
#include "Speed.h"
#include "MapChipCollider.h"
#include "SlimeActor.h"
#include "ParticleManager.h"

namespace YGame
{
	class MapChip;
}

class Character : 
	public CharaStatus, 
	public YGame::MapChipCollider, 
	public YGame::SlimeActor
{
protected:
	// オブジェクト
	std::unique_ptr<YGame::ModelObject> obj_;
	// 移動方向
	YMath::Vector3 move_;
	// スピード
	YMath::Speed speed_;
	// 向き
	YMath::Vector3 direction_;
	// 色
	std::unique_ptr<YGame::Color> color_;
public:
	// 初期化
	void Initialize(
		const CharaStatus::InitStatus& charaStatus, const YGame::Transform::Status& objStatus,
		const YMath::Vector3& acceleration, const YMath::Vector3& max, 
		const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f });
	// リセット
	void Reset(
		const CharaStatus::InitStatus& charaStatus, const YGame::Transform::Status& objStatus,
		const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f });
protected:
	// 重力 + マップチップアタリ判定 + アニメーション
	void UpdatePhysics();
	// ジャンプ + アニメーション
	void Jump();
	// 更新
	void Update();
public:
	// 位置取得
	YMath::Vector3 Pos() const { return obj_->pos_; };
	// 大きさ取得
	YMath::Vector3 Scale() const { return obj_->scale_; };
public:
	// 位置取得 (参照渡し)
	YMath::Vector3& PosRef() override { return obj_->pos_; }
	// スピード (参照渡し)
	YMath::Vector3& SpeedRef() override { return speed_.ValueRef(); }
protected:
	// 静的マップチップポインタ
	static YGame::MapChip* pMapChip_;
	// 静的パーティクルマネージャーポインタ
	static YGame::ParticleManager* pParticleMan_;
public:
	// 静的初期化設定
	struct StaticInitStatus 
	{
		YGame::MapChip* pMapChip_;
		YGame::ParticleManager* pParticleMan_;
	};
public:
	// 静的初期化
	static void StaticInitialize(const StaticInitStatus& state);
};

