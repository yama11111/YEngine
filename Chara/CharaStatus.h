#pragma once
#include "Timer.h"

class CharaStatus
{
private:
	// 体力
	int hp_ = 0;
	// 生存フラグ
	bool isAlive_ = true;
	// 無敵時間
	YMath::Timer cheatT_;
	// 無敵フラグ
	bool isCheat_ = false;
public:
	// 初期化ステータス
	struct InitStatus
	{
		int hp_; // 体力
		int chaetTime_; // 無敵時間
	};
public:
	// 初期化
	void InitializeCharaStatus(const InitStatus& state);
	// 更新
	void UpdateCharaStatus();
	// ダメージを受ける
	void Hit(const int damage);
public:
	// 生存フラグ
	bool isAlive() const { return isAlive_; }
	// 無敵フラグ
	bool isCheat() const { return isCheat_; }
public:
	// HP設定
	void SetHP(const int hp);
};

