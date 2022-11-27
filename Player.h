#pragma once
#include "Model.h"
#include "Collider.h"

class Player : Collision::Collider
{
private:
	// �I�u�W�F�N�g
	Game::Object obj_;

	// �W�����v��
	int jumpCount_ = 0;
	// �W�����v��
	float jumpPower_ = 0.0f;
	// �n�ʂɂ��邩
	bool isLanding_ = false;
public:
	// ������
	void Initialize();
	// ���Z�b�g
	void Reset();
	// �Փˎ�����
	void OnCollision(const uint32_t attribute) override;
	// �X�V
	void Update();
	// �`��
	void Draw(const Game::ViewProjection& vp);
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
public:
	// �ʒu�擾
	Math::Vec3 Pos() override { return obj_.pos_; };
private:
	// �ÓI���f���|�C���^
	static Game::Model* pModel_;
	// �ÓI�e�N�X�`���C���f�b�N�X
	static UINT tex_;
public:
	// �ÓI�������X�e�[�^�X
	struct StaticInitStatus
	{
		Game::Model* pModel_;// ���f���|�C���^
		UINT tex_;// �e�N�X�`���C���f�b�N�X
	};
public:
	// �ÓI������
	static void StaticIntialize(const StaticInitStatus& state);
};

