#pragma once
#include "Collider.h"

class Attack : public Collision::Collider 
{
private:
	YMath::Vec3 pos_;
	YMath::Vec3 scale_;
public:
	// ˆÊ’uŽæ“¾
	YMath::Vec3 Pos() const override { return pos_; };
	// ‘å‚«‚³Žæ“¾
	YMath::Vec3 Scale() const { return scale_; };
};

