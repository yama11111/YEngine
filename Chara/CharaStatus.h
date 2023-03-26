#pragma once
#include "Timer.h"

class CharaStatus
{
private:
	// �̗�
	int hp_ = 0;
	// �����t���O
	bool isAlive_ = true;
	// ���G����
	YMath::Timer cheatTim_;
	// ���G�t���O
	bool isCheat_ = false;
public:
	// �������X�e�[�^�X
	struct InitStatus
	{
		int hp_; // �̗�
		int chaetTime_; // ���G����
	};
public:
	// ������
	void Initialize(const InitStatus& status);
	// �X�V
	void Update();
	// �_���[�W���󂯂�
	void Hit(const int damage);
public:
	// �����t���O
	bool isAlive() const { return isAlive_; }
	// ���G�t���O
	bool isCheat() const { return isCheat_; }
public:
	// HP�ݒ�
	void SetHP(const int hp);
};

