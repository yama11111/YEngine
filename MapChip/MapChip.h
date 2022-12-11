#pragma once
#include "Model.h"
#include "Sprite.h"
#include "MapChipCollider.h"

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
	std::vector<std::vector<Game::Object>> chips_;
	// �}�b�v�`�b�v2D�p
	std::vector<std::vector<Game::Object>> chip2Ds_;
	// �}�b�v�S�̂̑傫��(��`)
	Math::Vec2 rect_;
	// �`�b�v1���̑傫��
	float chipSize_ = 0.0f;
	// ����
	Math::Vec3 leftTop_;

	// ���f���|�C���^
	Game::Model* pModel_ = nullptr;
	// �e�N�X�`���C���f�b�N�X
	UINT tex_ = UINT_MAX;
	// �X�v���C�g�|�C���^
	Game::Sprite* pSprite_ = nullptr;
public:
	// ���[�h�X�e�[�^�X
	struct LoadStatus
	{
		const std::string mapFileName_; // �}�b�v�t�@�C����
		Game::Model* pModel_; // ���f���|�C���^
		UINT tex_; // �e�N�X�`���C���f�b�N�X
		Game::Sprite* pSprite_; // �X�v���C�g�|�C���^
	};
	// �������X�e�[�^�X
	struct InitStatus 
	{
		float chipSize_; // �`�b�v1���̑傫��
		Math::Vec3 leftTop_; // ����([0][0])
	};
public:
	// ���[�h
	void Load(const LoadStatus& state);
	// ������
	void Initialize(const InitStatus& state);
	// ���Z�b�g
	void Reset(const Math::Vec3& leftTop);
	// �X�V
	void Update();
	// �`��
	void Draw(const Game::ViewProjection& vp);
	// 2D�`��
	void Draw2D();
public:
	// �Փˎ�����
	void PerfectPixelCollision(MapChipCollider& collider);
private:
	// ���ړ���̃`�b�v���Ƃ̃A�^������
	bool CollisionTemporaryMap(const Math::Vec3& pos, const Math::Vec3 scale, const Math::Vec3& spd);
	// �`�b�v���Ƃ̃A�^������
	bool CollisionMap(const float left, const float right, const float top, const float bottom);
	// �`�b�v���Ƃ̃A�^������
	bool CollisionChip(const int x, const int y);
	// �`�b�v�`��
	void DrawChip(const size_t x, const size_t y, const Game::ViewProjection& vp);
};