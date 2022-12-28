#pragma once
#include "Character.h"
#include "ViewProjection.h"

class MapChipPointer;

class Enemy : public Character
{
public:
	// 初期化ステータス
	struct InitStatus 
	{
		// 位置
		YMath::Vec3 pos_;
	};
public:
	// 初期化
	virtual void Initialize(const InitStatus& state) = 0;
	// リセット
	virtual void Reset(const InitStatus& state) = 0;
	// 衝突時処理
	void OnCollision(const uint32_t attribute, const YMath::Vec3& pos) override;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw(const YGame::ViewProjection& vp) = 0;
};

