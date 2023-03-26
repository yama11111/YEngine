#pragma once
#include "MapChip.h"

namespace YGame
{
	class MapChipManager
	{
	private:
		// �}�b�v�f�[�^
		std::vector<MapData> mapDatas_;
		// ���݂̃}�b�v�f�[�^�C���f�b�N�X
		uint32_t currentIndex_ = 0;
		// �}�b�v
		MapChip map_;
		// �}�b�v�\��
		MapChip2DDisplayer mapDisp_;
	public:
		// ���[�h�X�e�[�^�X
		struct LoadStatus
		{
			std::vector<Model*> pModels_; // ���f���|�C���^
			std::vector<Sprite2D*> pSprites_; // �X�v���C�g�|�C���^
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
		void Load(const LoadStatus& status);
		// ������
		void Initialize(const InitStatus& status);
		// ���Z�b�g
		void Reset();
		// �X�V
		void Update();
		// �`��
		void Draw();
		// 2D�`��
		void Draw2D();
	public:
		// ���݃}�b�v�|�C���^
		MapChip* CurrentMapPointer() { return &map_; }
	};
}

