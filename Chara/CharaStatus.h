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
	YMath::Timer cheatT_;
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
	void InitializeCharaStatus(const InitStatus& state);
	// �X�V
	void UpdateCharaStatus();
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

