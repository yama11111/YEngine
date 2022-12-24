#pragma once
#include "Model.h"
#include "Collider.h"
#include "MapChipCollider.h"

class MapChipPointer;

class Enemy : public Collision::Collider, public MapChipCollider
{
protected:
	// �I�u�W�F�N�g
	YGame::Object obj_;
	// �X�s�[�h
	YMath::Vec3 speed_;
public:
	// ���Z�b�g
	virtual void Reset() = 0;
	// �Փˎ�����
	void OnCollision(const uint32_t attribute) override;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw(const YGame::ViewProjection& vp) = 0;
public:
	// �ʒu�擾
	YMath::Vec3 Pos() const override { return obj_.pos_; };
	// �傫���擾
	YMath::Vec3 Scale() const { return obj_.scale_; };
public:
	// �ʒu�擾 (�Q�Ɠn��)
	YMath::Vec3& PosRef() override { return obj_.pos_; }
	// �X�s�[�h (�Q�Ɠn��)
	YMath::Vec3& SpeedRef() override { return speed_; }
protected:
	// �ÓI�}�b�v�`�b�v�|�C���^
	static MapChipPointer* pMapChip_;
public:
	// �ÓI�}�b�v�`�b�v�|�C���^�ݒ�
	static void SetMapChipPointer(MapChipPointer* pMapChip);
};

