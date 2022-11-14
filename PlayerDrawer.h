#pragma once
#include "PBody.h"
#include "PWeapon.h"
#include "PLeg.h"
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"

class PlayerDrawer
{
private:
	// Transform 省略
	using Trfm = Game::Transform;
private:
	// 核
	Trfm core_;
	// 体
	PBody body_;
	// 剣
	PWeapon sword_;
	// 足
	PLeg legs_[2]{};

	// 立ちモーション
	bool isIdle_ = false;

	bool isSwitchI_ = false;
	Math::Ease<Math::Vec3> idleBPE_;
	Math::Ease<Math::Vec3> idleSPE_;
	Math::Power idlePP_;

	// 歩きモーション
	bool isWalk_ = false;

	bool isSwitchW_ = false;
	Math::Ease<Math::Vec3> walkPE_;
	Math::Ease<Math::Vec3> walkRE_;
	Math::Power walkPP_;
	Math::Power walkRP_;

	bool isSwitchLeg_ = false;
	bool isFB = false;
	Math::Ease<Math::Vec3> walkLegFPE_[2];
	Math::Ease<Math::Vec3> walkLegBPE_[2];
	Math::Ease<Math::Vec3> walkLegFRE_[2];
	Math::Ease<Math::Vec3> walkLegBRE_[2];
	Math::Power walkLegP_;

	int walkJumpCount_ = 0;
	bool isSwitchJump_ = false;
	Math::Ease<Math::Vec3> walkJumpBPE_;
	Math::Ease<Math::Vec3> walkJumpSPE_;
	Math::Power walkJumpPP_;

public:
	// 初期化
	void Initialize(Math::Mat4* pPlayer);
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

