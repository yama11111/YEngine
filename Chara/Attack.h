#pragma once
#include "Collider.h"
#include "Timer.h"

class Attack : public Collision::Collider 
{
private:
	// 位置
	YMath::Vec3 pos_;
	// 機能タイマー
	YMath::Timer actTimer_;
public:

public:
	// 位置取得
	YMath::Vec3 Pos() const override { return pos_; };
};

