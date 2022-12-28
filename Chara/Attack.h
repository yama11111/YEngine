#pragma once
#include "Collider.h"

class Attack : public Collision::Collider 
{
private:
	YMath::Vec3 pos_;
	YMath::Vec3 scale_;
public:
	// 位置取得
	YMath::Vec3 Pos() const override { return pos_; };
	// 大きさ取得
	YMath::Vec3 Scale() const { return scale_; };
};

