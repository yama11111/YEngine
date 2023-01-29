#pragma once
#include "CharaStatus.h"
#include "Collider.h"
#include "MapChipCollider.h"
#include "SlimeActor.h"
#include "HitActor.h"
#include "ParticleManager.h"

class MapChipPointer;

class Character : 
	public CharaStatus, 
	public YCollision::Collider, 
	public MapChipCollider, 
	public YActor::SlimeActor,
	public YActor::HitActor
{
protected:
	// �I�u�W�F�N�g
	YGame::ObjectModel obj_;
	// �X�s�[�h
	YMath::Vec3 speed_;
	// 

public:
	// ������
	void InitializeCharacter(YGame::ObjectModel::Status state);
	// �d�͂ƃ}�b�v�`�b�v�A�^������ƃA�j���[�V����
	void UpdateGravity();
	// �X�V
	void UpdateCharacter();
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
	// �ÓI�p�[�e�B�N���}�l�[�W���[�|�C���^
	static YParticle::ParticleManager* pParticleMan_;
public:
	// �ÓI�������ݒ�
	struct StaticInitStatus 
	{
		MapChipPointer* pMapChip_;
		YParticle::ParticleManager* pParticleMan_;
	};
public:
	// �ÓI�}�b�v�`�b�v�|�C���^�ݒ�
	static void SetMapChipPointer(const StaticInitStatus& state);
};

