#pragma once
#include "Object.h"
#include "CharaStatus.h"
#include "Collider.h"
#include "MapChipCollider.h"

class MapChipPointer;

class Character : public CharaStatus ,public Collision::Collider, public MapChipCollider
{
protected:
	// �I�u�W�F�N�g
	YGame::Object obj_;
	// �X�s�[�h
	YMath::Vec3 speed_;
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

