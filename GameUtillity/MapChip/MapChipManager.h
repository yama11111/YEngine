#pragma once
#include "MapChip.h"

// �}�b�v�|�C���^
class MapChipPointer
{
private:
	// �|�C���^
	MapChip* pMapChip_ = nullptr;
public:
	// �}�b�v�`�b�v�Ƃ̃A�^������
	void Collision(MapChipCollider& collider);
	// �}�b�v�ݒ�
	void SetMapChip(MapChip* pMapChip) { pMapChip_ = pMapChip; }
};

class MapChipManager
{
private:
	// �}�b�v�f�[�^
	std::vector<MapChip> maps_;
	// ���݂̃}�b�v�C���f�b�N�X
	uint32_t currentIndex_ = 0;
	// ���݃}�b�v (����p)
	MapChipPointer current_{};
public:
	// ���[�h�X�e�[�^�X
	struct LoadStatus
	{
		YGame::Model* pModel_; // ���f���|�C���^
		UINT tex_; // �e�N�X�`���C���f�b�N�X
		YGame::Sprite2D* pSprite_; // �X�v���C�g�|�C���^
	};
	// �������X�e�[�^�X
	struct InitStatus
	{
		uint32_t mapIndex_; // �}�b�v�C���f�b�N�X
		YMath::Vector3 leftTop_; // ����([0][0])
		YMath::Vector3 chipSize_; // �`�b�v1���̑傫��
	};
public:
	// ���[�h
	void Load(const LoadStatus& state);
	// ������
	void Initialize(const InitStatus& state);
	// ���Z�b�g
	void Reset();
	// �X�V
	void Update();
	// �`��
	void Draw(const YGame::ViewProjection& vp);
	// 2D�`��
	void Draw2D();
public:
	// ���݃}�b�v�|�C���^
	MapChipPointer* CurrentMapPointer() { return &current_; }
};

