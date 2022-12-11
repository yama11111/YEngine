#pragma once
#include "Model.h"
#include "Collider.h"
#include "MapChipCollider.h"

class Player : public Collision::Collider, public MapChipCollider
{
private:
	// �I�u�W�F�N�g
	Game::Object obj_;
	// �X�s�[�h
	Math::Vec3 speed_;
	// �W�����v��
	int jumpCount_ = 0;
public:
	// ������
	void Initialize();
	// ���Z�b�g
	void Reset();
	// �Փˎ�����
	void OnCollision(const uint32_t attribute) override;
	// �X�V
	void Update();
	// �ړ��ʍX�V
	void UpdateMove();
	// �s��X�V
	void UpdateMatrix();
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
	Math::Vec3 Pos() const override { return obj_.pos_; };
	// �傫���擾
	Math::Vec3 Scale() const { return obj_.scale_; };
public:
	// �ʒu�擾 (�Q�Ɠn��)
	Math::Vec3& PosRef() override { return obj_.pos_; }
	// �X�s�[�h (�Q�Ɠn��)
	Math::Vec3& SpeedRef() override { return speed_; }
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

