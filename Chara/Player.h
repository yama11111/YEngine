#pragma once
#include "Character.h"
#include "Sprite2D.h"

class MapChipPointer;

class Player : public Character
{
private:
	YGame::ObjectSprite2D jump[2];
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
	void OnCollision(const uint32_t attribute, const YMath::Vec3& pos) override;
	// �X�V
	void Update();
	// �`��
	void Draw(const YGame::ViewProjection& vp);
	// 2D�`��
	void Draw2D();
public:
	// �W�����v
	void Jump();
	// �U��
	void Attack();
private:
	// �ړ��A�b�v�f�[�g
	void UpdateMove();
	// �W�����v�A�b�v�f�[�g
	void UpdateJump();
	// �U���A�b�v�f�[�g
	void UpdateAttack();
public:
	// �ʒu�|�C���^�擾
	YMath::Vec3* PosPointer() { return &obj_.pos_; }
private:
	// �ÓI���f���|�C���^
	static YGame::Model* pModel_;
	// �ÓI�X�v���C�g�|�C���^
	static YGame::Sprite2D* pJump_;
	// �ÓI�e�N�X�`���C���f�b�N�X
	static UINT tex_;
public:
	// �ÓI�������X�e�[�^�X
	struct StaticInitStatus
	{
		YGame::Model* pModel_;// ���f���|�C���^
		YGame::Sprite2D* pSprite_;
		UINT tex_;// �e�N�X�`���C���f�b�N�X
	};
public:
	// �ÓI������
	static void StaticIntialize(const StaticInitStatus& state);
};

