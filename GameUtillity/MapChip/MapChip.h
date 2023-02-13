#pragma once
#include "Model.h"
#include "Sprite2D.h"
#include "MapChipCollider.h"
#include <list>
#include <memory>

// �}�b�v���
class MapChipInfo
{
protected:
	// �}�b�v�`�b�v�i���o�[
	std::vector<std::vector<int>> chipNums_;
	// ���[�h�ς݂�
	bool isLoaded_ = false;
public:
	// csv�ǂݍ���
	void LoadData(const std::string fileName);
};

class MapChip : public MapChipInfo 
{
private:
	// �}�b�v�`�b�v
	std::vector<std::unique_ptr<YGame::ObjectModel>> chips_;
	//// �}�b�v�`�b�v2D�p
	//std::vector<std::vector<YGame::Object>> chip2Ds_;
	// �}�b�v�S�̂̑傫��(��`)
	YMath::Vector2 rect_;
	// �`�b�v1���̑傫��
	YMath::Vector3 chipSize_;
	// ����
	YMath::Vector3 leftTop_;

	// ���f���|�C���^
	YGame::Model* pModel_ = nullptr;
	// �e�N�X�`���C���f�b�N�X
	UINT tex_ = UINT_MAX;
	// �X�v���C�g�|�C���^
	YGame::Sprite2D* pSprite_ = nullptr;
public:
	// ���[�h�X�e�[�^�X
	struct LoadStatus
	{
		const std::string mapFileName_; // �}�b�v�t�@�C����
		YGame::Model* pModel_; // ���f���|�C���^
		UINT tex_; // �e�N�X�`���C���f�b�N�X
		YGame::Sprite2D* pSprite_; // �X�v���C�g�|�C���^
	};
	// �������X�e�[�^�X
	struct InitStatus 
	{
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
	// �Փˎ�����
	void PerfectPixelCollision(MapChipCollider& collider);
private:
	// ���ړ���̃`�b�v���Ƃ̃A�^������
	bool CollisionTemporaryMap(const YMath::Vector3& pos, const YMath::Vector3 scale, const YMath::Vector3& spd);
	// �`�b�v���Ƃ̃A�^������
	bool CollisionMap(const float left, const float right, const float top, const float bottom);
	// �`�b�v���Ƃ̃A�^������
	bool CollisionChip(const int x, const int y);
};