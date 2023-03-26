#pragma once
#include "CharaStatus.h"
#include "Speed.h"
#include "MapChipCollider.h"
#include "SlimeActor.h"
#include "ParticleManager.h"

namespace YGame
{
	class MapChip;
}

class Character : 
	public CharaStatus, 
	public YGame::MapChipCollider, 
	public YGame::SlimeActor
{
protected:
	// �I�u�W�F�N�g
	std::unique_ptr<YGame::ModelObject> obj_;
	// �ړ�����
	YMath::Vector3 move_;
	// �X�s�[�h
	YMath::Speed speed_;
	// ����
	YMath::Vector3 direction_;
	// �F
	std::unique_ptr<YGame::Color> color_;
public:
	// ������
	void Initialize(
		const CharaStatus::InitStatus& charaStatus, const YGame::Transform::Status& objStatus,
		const YMath::Vector3& acceleration, const YMath::Vector3& max, 
		const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f });
	// ���Z�b�g
	void Reset(
		const CharaStatus::InitStatus& charaStatus, const YGame::Transform::Status& objStatus,
		const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f });
protected:
	// �d�� + �}�b�v�`�b�v�A�^������ + �A�j���[�V����
	void UpdatePhysics();
	// �W�����v + �A�j���[�V����
	void Jump();
	// �X�V
	void Update();
public:
	// �ʒu�擾
	YMath::Vector3 Pos() const { return obj_->pos_; };
	// �傫���擾
	YMath::Vector3 Scale() const { return obj_->scale_; };
public:
	// �ʒu�擾 (�Q�Ɠn��)
	YMath::Vector3& PosRef() override { return obj_->pos_; }
	// �X�s�[�h (�Q�Ɠn��)
	YMath::Vector3& SpeedRef() override { return speed_.ValueRef(); }
protected:
	// �ÓI�}�b�v�`�b�v�|�C���^
	static YGame::MapChip* pMapChip_;
	// �ÓI�p�[�e�B�N���}�l�[�W���[�|�C���^
	static YGame::ParticleManager* pParticleMan_;
public:
	// �ÓI�������ݒ�
	struct StaticInitStatus 
	{
		YGame::MapChip* pMapChip_;
		YGame::ParticleManager* pParticleMan_;
	};
public:
	// �ÓI������
	static void StaticInitialize(const StaticInitStatus& state);
};

