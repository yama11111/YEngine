#pragma once
#include "Collider.h"
#include "Timer.h"

class Attack : public YCollision::Collider 
{
private:
	// �ʒu
	YMath::Vec3 pos_;
	// �@�\�^�C�}�[
	YMath::Timer actTimer_;
	// �����Ă��邩
	bool isAct_ = false;
public:
	// �������X�e�[�^�X
	struct InitStatus 
	{
		YMath::Vec3 pos_; // �ʒu
		float rad_; // ���a
		uint32_t attribute_; // ���� (����)
		uint32_t mask_; // �}�X�N (����)
		uint32_t actFrame_; // ����
	};
public:
	// ������
	void Initialize(const InitStatus& state);
	// �X�V
	void Update();
public:
	// �ʒu�擾
	YMath::Vec3 Pos() const override { return pos_; }
	// �����Ă��邩
	bool IsAct() const { return isAct_; }
};

