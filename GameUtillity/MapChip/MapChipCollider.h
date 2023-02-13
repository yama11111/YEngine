#pragma once
#include "Vector2.h"
#include "Vector3.h"

class MapChipCollider
{
private:
	YMath::Vector3 scale_; // 大きさ
	bool isLanding_ = false; // 地上にいるか 
	bool isElderLanding_ = false; // 地上にいたか 
public:
	struct InitStatus
	{
		YMath::Vector3 scale_; // 大きさ
	};
public:
	// マップ衝突設定初期化
	void InitializeMapCollisionStatus(const InitStatus& state);
public:
	// 位置取得 (参照)
	virtual YMath::Vector3& PosRef() = 0;
	// 大きさ取得
	YMath::Vector3 Scale() const { return scale_; }
	// スピード取得 (参照)
	virtual YMath::Vector3& SpeedRef() = 0;
	// 地上にいるか
	bool IsLanding() const { return isLanding_; }
	// 地上にいたか
	bool IsElderLanding() const { return isElderLanding_; }
	// 地上にいるか設定
	void SetIsLanding(const bool isLanding) { isLanding_ = isLanding; }
	// 地上にいたか設定
	void SetIsElderLanding(const bool isElderLanding) { isElderLanding_ = isElderLanding; }
};

