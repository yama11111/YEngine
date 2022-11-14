#pragma once
#include "EBody.h"
#include "EWing.h"
#include "EWeapon.h"
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"

class EnemyDrawer
{
private:
	// Transform 省略
	using Trfm = Game::Transform;
private:
	// 核
	Trfm core_;
	// 体
	EBody body_;
	// 翼
	EWing wing_;
	// 剣
	EWeapon sword_[2]{};

	// 立ちモーション
	bool isIdle_ = false;

	bool isSwitchI_ = false;
	Math::Ease<Math::Vec3> idleBPE_;
	Math::Ease<Math::Vec3> idleWPE_;
	Math::Ease<Math::Vec3> idleWFE_;
	Math::Ease<Math::Vec3> idleSPE_[2];
	Math::Ease<Math::Vec3> idleSTE_[2];
	Math::Power idlePP_;

	// 歩きモーション
	bool isWalk_ = false;

	Math::Ease<Math::Vec3> walkRE_;
	Math::Power walkRP_;

	Math::Ease<Math::Vec3> walkFlySPE_;
	Math::Ease<Math::Vec3> walkFlySTE_[2];
	Math::Power walkFlyPP_;

public:
	// 初期化
	void Initialize(Math::Mat4* pEnemy);
	// リセット
	void Reset();
	// 更新
	void Update();
	// 描画
	void Draw(Game::ViewProjection& vp);
public:
	// 
	void SetWalkActivate(const bool isAct) { isWalk_ = isAct; }
	// 
private:
	// 
	void UpdateIdle();
	// 
	void UpdateWalking();
	// 
	void UpdateAttack();
	// 
	void UpdateFinal();
private:
	// 静的モデルポインタ
	static Game::Model* pModel_;
	// テクスチャ
	static UINT tex_;
public:
	// 静的初期化
	static void StaticInitialize(Game::Model* pModel, const UINT tex);
};

