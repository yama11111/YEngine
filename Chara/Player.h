#pragma once
#include "Character.h"
#include "Model.h"

class MapChipPointer;

class Player : public Character
{
private:
	// �W�����v��
	int jumpCount_ = 0;
public:
	// �������X�e�[�^�X
	struct InitStatus
	{
		// �ʒu
		YMath::Vec3 pos_;
	};
public:
	// ������
	virtual void Initialize(const InitStatus& state);
	// ���Z�b�g
	void Reset(const InitStatus& state);
	// �Փˎ�����
	void OnCollision(const uint32_t attribute) override;
	// �X�V
	void Update();
	// �`��
	void Draw(const YGame::ViewProjection& vp);
public:
	// �W�����v
	void Jump();
	// �U��
	void Attack();
private:
	// �W�����v�A�b�v�f�[�g
	void UpdateJump();
	// �U���A�b�v�f�[�g
	void UpdateAttack();
private:
	// �ÓI���f���|�C���^
	static YGame::Model* pModel_;
	// �ÓI�e�N�X�`���C���f�b�N�X
	static UINT tex_;
public:
	// �ÓI�������X�e�[�^�X
	struct StaticInitStatus
	{
		YGame::Model* pModel_;// ���f���|�C���^
		UINT tex_;// �e�N�X�`���C���f�b�N�X
	};
public:
	// �ÓI������
	static void StaticIntialize(const StaticInitStatus& state);
};

