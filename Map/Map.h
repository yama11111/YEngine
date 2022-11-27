#pragma once
#include "Model.h"

class MapInfo
{
protected:
	// �}�b�v�`�b�v�i���o�[
	std::vector<std::vector<int>> chipNums_;
	// ���[�h�ς݂�
	bool isLoaded_ = false;
public:
	// csv�ǂݍ���
	void Load(const std::string fileName);
};

class Map : public MapInfo 
{
private:
	// �}�b�v�`�b�v
	std::vector<std::vector<Game::Object>> chips_;
	// �}�b�v�S�̂̑傫��(��`)
	Math::Vec2 rect_;
	// �`�b�v1���̑傫��
	float chipSize_ = 0.0f;

	// ���f���|�C���^
	Game::Model* pModel_ = nullptr;
	// �e�N�X�`���C���f�b�N�X
	UINT tex_ = UINT_MAX;
public:
	// �������X�e�[�^�X
	struct InitStatus 
	{
		float chipSize_; // �`�b�v1���̑傫��
		Math::Vec3 leftTop_; // ����([0][0])
		Game::Model* pModel_; // ���f���|�C���^
		UINT tex_; // �e�N�X�`���C���f�b�N�X
	};
public:
	// ������
	void Initialize(const InitStatus& state);
	// ���Z�b�g
	void Reset(const Math::Vec3& leftTop);
	// �X�V
	void Update();
	// �`��
	void Draw(const Game::ViewProjection& vp);
public:
	// �Փˎ�����
	void PerfectPixelCollision(Math::Vec3& pos, const Math::Vec3 scale, Math::Vec2& spd);
private:
	// ���ړ���̃`�b�v���Ƃ̃A�^������
	bool TemporaryChipCollision(Math::Vec3& pos, const Math::Vec3 scale, const Math::Vec2& spd);
	// �`�b�v���Ƃ̃A�^������
	bool ChipCollision(const float left, const float right, const float top, const float bottom);
};