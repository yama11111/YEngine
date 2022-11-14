#pragma once
#include "EBody.h"
#include "EWing.h"
#include "EWeapon.h"

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

	Math::Power idlePP_;

	// 歩きモーション
	bool isWalk_ = false;

	Math::Ease<Math::Vec3> walkRE_;
	Math::Power walkRP_;

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

