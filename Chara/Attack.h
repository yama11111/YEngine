#pragma once
#include "Collider.h"

class Attack : public Collision::Collider 
{
private:
	YMath::Vec3 pos_;
	YMath::Vec3 scale_;
public:
	// �ʒu�擾
	YMath::Vec3 Pos() const override { return pos_; };
	// �傫���擾
	YMath::Vec3 Scale() const { return scale_; };
};

