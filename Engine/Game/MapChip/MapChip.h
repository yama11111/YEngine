#pragma once
#include "Sprite2D.h"
#include "MapChipCollider.h"
#include <memory>

namespace YGame
{
	// �}�b�v���
	struct MapData
	{
	public:
		// �}�b�v�`�b�v�ԍ�
		std::vector<std::vector<int>> chipNums_;
		// �}�b�v�`�b�v�A�^������
		std::vector<std::vector<bool>> chipColls_;

		// ���[�h�ς݂�
		bool isLoaded_ = false;
	public:
		// csv�ǂݍ���
		void Load(const std::string fileName);
		// ����
		void Clear();
		// �R���W�������Z�b�g
		void CollReset();
	};

	// �}�b�v�`�b�v
	class MapChip
	{
	private:
		// �`�b�v1�̏��
		struct Chip
		{
			std::unique_ptr<Transform> transform_; // �g�����X�t�H�[��
		};
	private:
		// �}�b�v�`�b�v
		std::vector<std::unique_ptr<Chip>> chips_;
		
		// �}�b�v�f�[�^�|�C���^
		MapData* pMapData_ = nullptr;
		
		// �`�b�v1���̑傫��
		YMath::Vector3 chipScale_;
		// ����([0][0])
		YMath::Vector3 leftTop_;
	public:
		// ������ (�}�b�v�f�[�^������ver)
		void Initialize(MapData* pMapData, const YMath::Vector3& leftTop, const YMath::Vector3& chipScale);
		// ������
		void Initialize(const YMath::Vector3& leftTop, const YMath::Vector3& chipScale);
		// ���Z�b�g
		void Reset();
		// �X�V
		void Update();
		// �`��
		void Draw();
	public:
		// �Փˎ�����
		void PerfectPixelCollision(MapChipCollider& collider);
		// �傫�� (��`)
		YMath::Vector2 Size();
	private:
		// ���ړ���̃`�b�v���Ƃ̃A�^������
		bool CollisionTemporaryMap(const YMath::Vector3& pos, const YMath::Vector3 scale, const YMath::Vector3& spd);
		// �`�b�v���Ƃ̃A�^������
		bool CollisionMap(const float left, const float right, const float top, const float bottom);
		// �`�b�v���Ƃ̃A�^������
		bool CollisionChip(const int x, const int y);
	};

	// �}�b�v�`�b�v2D�\���p
	class MapChip2DDisplayer
	{
	private:
		// �`�b�v1�̏��
		struct Chip
		{
			std::unique_ptr<Sprite2D::Object> obj_; // �萔�o�b�t�@
			std::unique_ptr<CBColor> color_;
		};
	private:
		// �}�b�v�`�b�v2D
		std::vector<std::vector<std::unique_ptr<Chip>>> chips_;

		// �}�b�v�f�[�^�|�C���^
		MapData* pMapData_ = nullptr;
	public:
		// ������
		void Initialize(MapData* pMapData);
		// �X�V
		void Update();
		// �`��
		void Draw();
	};
}
