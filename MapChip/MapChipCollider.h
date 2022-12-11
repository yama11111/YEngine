#pragma once
#include "Vec2.h"
#include "Vec3.h"

class MapChipCollider
{
private:
	Math::Vec3 scale_; // 大きさ
	bool isLanding_ = false; // 地上にいるか
public:
	struct InitStatus
	{
		Math::Vec3 scale_; // 大きさ
		bool isLanding_ = false; // 地上にいるか
	};
public:
	// マップ衝突設定初期化
	void InitializeMapCollisionStatus(const InitStatus& state);
public:
	// 位置取得 (参照)
	virtual Math::Vec3& PosRef() = 0;
	// 大きさ取得
	Math::Vec3 Scale() const { return scale_; }
	// スピード取得 (参照)
	virtual Math::Vec3& SpeedRef() = 0;
	// 地上にいるか
	bool IsLanding() const { return isLanding_; }
	// 地上フラグ設定
	void SetIsLanding(const bool isLanding) { isLanding_ = isLanding; };
};

