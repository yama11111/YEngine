#pragma once
#include "Collider.h"
#include "Timer.h"

class Attack : public Collision::Collider 
{
private:
	// �ʒu
	YMath::Vec3 pos_;
	// �@�\�^�C�}�[
	YMath::Timer actTimer_;
public:

public:
	// �ʒu�擾
	YMath::Vec3 Pos() const override { return pos_; };
};

